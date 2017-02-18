#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <thread>
#include <memory>

#include "render_text.h"
#include "graphic/bitmap.h"
#include "graphic/canvas.h"

#include "event_processor.h"
#include "painter.h"

namespace le {
namespace web {

namespace {


pollfd pollfds[100];
int pollfds_size = 0;
#define MAX_POLL_ELEMENTS 100


void PrintReason(lws_callback_reasons reason)
{
  switch(reason) {
    case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
      std::cout << "change mode pool" << std::endl;
      break;
    case LWS_CALLBACK_LOCK_POLL:
      std::cout << "lock poll "<< std::endl;
      break;
    case LWS_CALLBACK_UNLOCK_POLL:
      std::cout << "unlock poll "<< std::endl;
      break;
    case LWS_CALLBACK_ADD_POLL_FD:
      std::cout << "add pool fd "<< std::endl;
      break;
    case LWS_CALLBACK_DEL_POLL_FD:
      std::cout << "delete pool fd "<< std::endl;
      break;

    case LWS_CALLBACK_PROTOCOL_INIT:
      std::cout << "protocol init "<< std::endl;
      break;
  }
}


int CallBackLe(lws* wsi,
               lws_callback_reasons reason,
               void *user,
               void *in, size_t len)
{


  switch (reason) {
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection client established\n");
      break;

    case LWS_CALLBACK_ESTABLISHED: {
      printf("connection established\n");
      auto event_processor_map = static_cast<std::unordered_map<lws*, EventProcessor*>*>(lws_get_protocol(wsi)->user);
      event_processor_map->emplace(wsi, new EventProcessor(wsi));
      // auto rendertext = new RenderText();
      // std::cout << "user : " << user << std::endl;
      // rendertext_map->emplace(wsi, rendertext);
      break;
    }
    case LWS_CALLBACK_CLOSED: {
      auto event_processor_map = static_cast<std::unordered_map<lws*, EventProcessor*>*>(lws_get_protocol(wsi)->user);
      auto it = event_processor_map->find(wsi);
      if( it != event_processor_map->end() ) {
        auto removed = it->second;
        event_processor_map->erase(wsi);
        delete removed;

      }
      
      // auto rendertext_map = static_cast<std::unordered_map<lws*, RenderText*>*>(lws_get_protocol(wsi)->user);
      // printf("connection closed\n");
      // rendertext_map->erase(wsi);
      break;
    }
    case LWS_CALLBACK_RECEIVE: {
      auto event_processor_map = static_cast<std::unordered_map<lws*, EventProcessor*>*>(lws_get_protocol(wsi)->user);
      // auto rendertext_map = static_cast<std::unordered_map<lws*, RenderText*>*>(lws_get_protocol(wsi)->user);
      std::string str = reinterpret_cast<char*>(in);
      std::cout << str << std::endl;
      auto it = event_processor_map->find(wsi);
      if( it != event_processor_map->end() ) {
        it->second->PushEvent(str);
        it->second->PushEvent("{\"type\":\"paint\"}");
      }
      break;
    }
    default:
      PrintReason(reason);
      break;
  }

  return 0;
  
}



int CallBackHttp(lws* wsi,
                 lws_callback_reasons reason,
                 void *user,
                 void *in, size_t len)
{
  auto session_map = static_cast<std::unordered_map<std::string, int>*>(lws_get_protocol(wsi)->user);
  lws_pollargs *pa = (struct lws_pollargs *)in;
  
  switch (reason) {
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection client established\n");
      break;
    case LWS_CALLBACK_HTTP: {
      char *requested_uri = (char *) in;
      auto pid = fork();
      if( pid == 0 ) {
        Session session;
        session.Start();
      }
      session_map->emplace(requested_uri, pid);
      printf("requested URI: %s\n", requested_uri);
      lws_serve_http_file(wsi, "../../src/web/index.html", "text/html", nullptr, 0);
      break;
    }
    case LWS_CALLBACK_ADD_POLL_FD: {

      pollfds[pollfds_size].fd = pa->fd;
      pollfds[pollfds_size].events = pa->events;
      pollfds[pollfds_size++].revents = 0;

      std::cout << "add pool fd!!! "<< pa->fd <<std::endl;
      break;
    }

    case LWS_CALLBACK_DEL_POLL_FD:
      std::cout << "DELETE POLL!"<< std::endl;
      for (int n = 0; n < pollfds_size; n++)
        if (pollfds[n].fd == pa->fd)
          while (n < pollfds_size) {
            pollfds[n] = pollfds[n + 1];
            n++;
          }
      pollfds_size--;
      break;

    case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
      std::cout << "CHANGE MODE POLL!"<< std::endl;
      for (int n = 0; n < pollfds_size; n++)
        if (pollfds[n].fd == pa->fd)
          pollfds[n].events = pa->events;
      break;

    // case LWS_CALLBACK_CLEAR_MODE_POLL_FD:
    //   for (int n = 0; n < pollfds_size; n++)
    //     if (pollfds[n].fd == (int)(long)user)
    //       pollfds[n].events &= ~(int)(long)len;
    //   break;
      
      
    default:
      PrintReason(reason);
      break;
  }
  return 0;
}

}

Server::Server()
{

}

Server::~Server()
{

}

void Server::Start()
{
  int port = 8080;
  const char *interface = NULL;
  lws_context *context;
  int opts = 0;

  lws_protocols protocols[] = {
    { "http_protocol", CallBackHttp, 0, 0, },
    // { "le_web_protocol", CallBackLe, 0, 0, 0, &event_processor_map_, },
    { nullptr, nullptr, 0 }
  };

  lws_context_creation_info info;
  memset(&info, 0, sizeof(info));
  
  info.port = port;
  info.iface = interface;
  info.protocols = protocols;
  info.extensions = nullptr;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = opts;

  context = lws_create_context(&info);

  le::RenderText rendertext;

  if (context == nullptr) {
    fprintf(stderr, "libwebsocket init failed\n");
    return;
  }

  printf("starting server...\n");

  while (1) {
    // auto n = lws_service(context, 50);

    auto n = poll(pollfds, pollfds_size, 25);

    if ( n < 0 ) {
      exit(1);
    }
    if(n) {
      for (int i = 0; i < pollfds_size; ++i) {
        if( pollfds[i].revents ) {
          auto res = lws_service_fd(context, &pollfds[i]);
        }
      }
    }
  }

  lws_context_destroy(context);
}


}  // web
}  // le

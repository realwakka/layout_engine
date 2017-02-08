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
    case LWS_CALLBACK_GET_THREAD_ID: {
      std::cout << "thread!!" << std::endl;
      std::cout<< "pid : " << getpid() << std::endl;
      return getpid();
    }
    case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
      std::cout << "change mode pool\n" << std::endl;
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
    default:
      std::cout << "unhandled callback " << reason << std::endl;
      break;
  }

  return 0;
  
}



int CallBackHttp(lws* wsi,
                 lws_callback_reasons reason,
                 void *user,
                 void *in, size_t len)
{
  switch (reason) {
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection client established\n");
      break;
    case LWS_CALLBACK_HTTP: {
      char *requested_uri = (char *) in;
      printf("requested URI: %s\n", requested_uri);

      lws_serve_http_file(wsi, "../../src/web/index.html", "text/html", nullptr, 0);
      break;
    }
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
    { "le_web_protocol", CallBackLe, 0, 0, 0, &event_processor_map_, },
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
    auto n = lws_service(context, 50);
  }

  lws_context_destroy(context);
}


}  // web
}  // le

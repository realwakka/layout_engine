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
      break;
    }
    case LWS_CALLBACK_RECEIVE: {
      auto event_processor_map = static_cast<std::unordered_map<lws*, EventProcessor*>*>(lws_get_protocol(wsi)->user);
      std::string str = reinterpret_cast<char*>(in);
      std::cout << str << std::endl;
      auto it = event_processor_map->find(wsi);
      if( it != event_processor_map->end() ) {
        it->second->PushEvent(str);
        // it->second->PushEvent("{\"type\":\"paint\"}");
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
  switch (reason) {
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection client established\n");
      break;
    case LWS_CALLBACK_HTTP: {
      std::string uri(static_cast<char*>(in));
      std::cout << "requested URI: "<< uri << std::endl;
      std::string base("../../src/web");
      if( uri == "/" ) {
	lws_serve_http_file(wsi, "../../src/web/index.html", "text/html", nullptr, 0);
      } else {
	lws_serve_http_file(wsi, (base + uri).c_str(), "text/html", nullptr, 0);
      }
      
      break;
    }
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

  while (true) {
    auto n = lws_service(context, 50);
  }

  lws_context_destroy(context);
}


}  // web
}  // le

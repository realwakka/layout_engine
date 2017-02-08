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
      auto rendertext_map = static_cast<std::unordered_map<lws*, RenderText*>*>(lws_get_protocol(wsi)->user);
      printf("connection established\n");
      auto rendertext = new RenderText();

      std::cout << "user : " << user << std::endl;

      rendertext_map->emplace(wsi, rendertext);
      break;
    }
    case LWS_CALLBACK_CLOSED: {
      auto rendertext_map = static_cast<std::unordered_map<lws*, RenderText*>*>(lws_get_protocol(wsi)->user);
      printf("connection closed\n");
      rendertext_map->erase(wsi);
      break;
    }
    case LWS_CALLBACK_RECEIVE: {
      auto rendertext_map = static_cast<std::unordered_map<lws*, RenderText*>*>(lws_get_protocol(wsi)->user);
      std::string str = reinterpret_cast<char*>(in);
      std::cout << str << std::endl;
      auto it = rendertext_map->find(wsi);
      if( it != rendertext_map->end() ) {
        auto&& rendertext = *it->second;
        EventProcessor event_processor;
        event_processor.ProcessEvent(str, rendertext);

        Painter painter;
        auto out =  painter.PaintToPng(rendertext);
        std::unique_ptr<unsigned char[]> send_data(new unsigned char[LWS_PRE + out.size()]);
        //unsigned char* send_data = new unsigned char[LWS_PRE + out.size()];
        std::memcpy(&send_data.get()[LWS_PRE], out.data(), out.size());
        

        lws_write(wsi, (unsigned char*)&send_data.get()[LWS_PRE], out.size(), LWS_WRITE_BINARY);

        //delete[] send_data;
        
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
    /* first protocol must always be HTTP handler */
    { "http_protocol", CallBackHttp, 0, 0, },
    { "le_web_protocol", CallBackLe, 0, 0, 0, &rendertext_map_, },
    { NULL, NULL, 0 }
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
  

  if (context == NULL) {
    fprintf(stderr, "libwebsocket init failed\n");
    return;
  }

  printf("starting server...\n");

  // infinite loop, to end this server send SIGTERM. (CTRL+C)
  while (1) {
    auto n = lws_service(context, 50);
  }

  lws_context_destroy(context);
}


}  // web
}  // le

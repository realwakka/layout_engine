#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libwebsockets.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

namespace le {
namespace web {

namespace {

int callback_http(lws* wsi,
                  lws_callback_reasons reason,
                  void *user,
                  void *in, size_t len)
{
  switch (reason) {
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection client established\n");
      break;
    case LWS_CALLBACK_HTTP: {
      // auto universal_response = "Hello, World!";
      // libwebsocket_write(wsi, (unsigned char*)universal_response, strlen(universal_response), LWS_WRITE_HTTP);
      // break;
      char *requested_uri = (char *) in;
      printf("requested URI: %s\n", requested_uri);

      lws_serve_http_file(wsi, "index.html", "text/html", nullptr, 0);

      // close connection
      // libwebsocket_close_and_free_session(context, wsi,
      //                                     LWS_CLOSE_STATUS_NORMAL);
      break;
    }

    case LWS_CALLBACK_ESTABLISHED:
      printf("connection established\n");
      user = new int(5);
      std::cout << "user : " << user << std::endl;
      break;
    case LWS_CALLBACK_CLOSED:
      printf("connection closed\n");
      break;
    case LWS_CALLBACK_RECEIVE: {
      std::cout << "user : " << user << std::endl;
      std::string str = reinterpret_cast<char*>(in);
      std::cout << str << std::endl;
      //std::reverse(str.begin(), str.end());
      lws_write(wsi, (unsigned char*)str.c_str(), str.size(), LWS_WRITE_TEXT);
      break;
    }
    case LWS_CALLBACK_GET_THREAD_ID: {
      std::cout<< "pid : " << getpid() << std::endl;
      return getpid();
    }
    default:
      printf("unhandled callback %d\n", reason);
      break;
  }

  return 0;
}

lws_protocols protocols[] = {
  /* first protocol must always be HTTP handler */
  {
    "le_web_protocol",
    callback_http,
    0,
    0,
  },
  {
    NULL, NULL, 0   /* End of list */
  }
};


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

  lws_context_creation_info info;
  memset(&info, 0, sizeof(info));
  
  info.port = port;
  info.iface = interface;
  info.protocols = protocols;
  info.extensions = nullptr;
  //if (!use_ssl) {
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  //} else {
  //  info.ssl_cert_filepath = LOCAL_RESOURCE_PATH"/libwebsockets-test-server.pem";
  //  info.ssl_private_key_filepath = LOCAL_RESOURCE_PATH"/libwebsockets-test-server.key.pem";
  //}
  info.gid = -1;
  info.uid = -1;
  info.options = opts;

  context = lws_create_context(&info);
  

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

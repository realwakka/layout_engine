#include "session.h"

#include <iostream>

namespace le {
namespace web {

namespace {

int CallBackEvent(lws* wsi,
                  lws_callback_reasons reason,
                  void *user,
                  void *in, size_t len)
{
  switch(reason) {
    case LWS_CALLBACK_ESTABLISHED: {
      printf("SSSSSSSSSSS connection established\n");
      break;
    }

    case LWS_CALLBACK_CLOSED: {
      printf("SSSSSSSSSSSSconnection closed\n");
      break;
    }
    case LWS_CALLBACK_RECEIVE: {
      std::string str = reinterpret_cast<char*>(in);
      std::cout << str << std::endl;
      break;
    }
      
    default:
      break;
  }
}

}

Session::Session()
    : exit_(false)
{}
Session::~Session()
{}

void Session::Start()
{
  lws_context *context;
  lws_protocols protocols[] = {
    { "le_web_protocol", CallBackEvent, 0, 0, 0, &rendertext_, },
    { nullptr, nullptr, 0 }
  };

  lws_context_creation_info info;
  memset(&info, 0, sizeof(info));
  
  info.port = 8080;
  info.iface = nullptr;
  info.protocols = protocols;
  info.extensions = nullptr;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = 0;

  context = lws_create_context(&info);

  while(exit == false) {
    auto n = lws_service(context, 50);
  }
  
  
}


}  // web
}  // le

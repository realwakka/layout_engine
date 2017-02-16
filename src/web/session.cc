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
      printf("connection established\n");
      break;
    }

    case LWS_CALLBACK_CLOSED: {
      printf("connection closed\n");
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
  
}


}  // web
}  // le

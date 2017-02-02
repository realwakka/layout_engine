#include <memory>
#include <cstdint>
#include <iostream>
#include <evhttp.h>
int main()
{
  if (!event_init())
  {
    std::cerr << "Failed to init libevent." << std::endl;
    return -1;
  }
  char const SrvAddress[] = "127.0.0.1";
  std::uint16_t SrvPort = 5555;
  std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);
  if (!Server)
  {
    std::cerr << "Failed to init http server." << std::endl;
    return -1;
  }
  void (*OnReq)(evhttp_request *req, void *) = [] (evhttp_request *req, void *)
  {
    auto *OutBuf = evhttp_request_get_output_buffer(req);
    if (!OutBuf)
      return;
    evbuffer_add_printf(OutBuf, "<html><body><center><h1>Hello World!</h1></center></body></html>");
    evhttp_send_reply(req, HTTP_OK, "", OutBuf);
  };
  evhttp_set_gencb(Server.get(), OnReq, nullptr);

  auto bound_socket = evhttp_bind_socket_with_handle(Server.get(), "0.0.0.0", 8080);
  auto fd = evhttp_bound_socket_get_fd(bound_socket);
  
  if (event_dispatch() == -1)
  {
    std::cerr << "Failed to run messahe loop." << std::endl;
    return -1;
  }
  return 0;
}






// #include <sys/types.h>
// #include <sys/time.h>
// #include <sys/queue.h>
// #include <stdlib.h>
// #include <err.h>
// #include <event.h>
// #include <evhttp.h>
// #include <iostream>

// void generic_handler(struct evhttp_request *req, void *arg)
// {
//   std::cout << "generic handler"<< std::endl;
  
//   struct evbuffer *buf;
//   buf = evbuffer_new();
//   if (buf == NULL)
//     err(1, "failed to create response buffer");
//   evbuffer_add_printf(buf, "Requested: %sn", evhttp_request_uri(req));
//   evhttp_send_reply(req, HTTP_OK, "OK", buf);
// }

// int main(int argc, char **argv)
// {

//   event_init();
//   //httpd = evhttp_start("0.0.0.0", 8080);

//   auto base = event_base_new();
//   auto httpd = evhttp_new(base);

//   /* Set a callback for requests to "/specific". */
//   /* evhttp_set_cb(httpd, "/specific", another_handler, NULL); */


//   /* Set a callback for all other requests. */
//   evhttp_set_gencb(httpd, generic_handler, NULL);

//   auto bound_socket = evhttp_bind_socket_with_handle(httpd, "0.0.0.0", 8080);
//   auto fd = evhttp_bound_socket_get_fd(bound_socket);

//   event_dispatch();    /* Not reached in this code as it is now. */
//   evhttp_free(httpd);

//   return 0;
// }

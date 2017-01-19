#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <err.h>
#include <event.h>
#include <evhttp.h>
#include <iostream>

void generic_handler(struct evhttp_request *req, void *arg)
{
  std::cout << "generic handler"<< std::endl;
  
  struct evbuffer *buf;
  buf = evbuffer_new();
  if (buf == NULL)
    err(1, "failed to create response buffer");
  evbuffer_add_printf(buf, "Requested: %sn", evhttp_request_uri(req));
  evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

int main(int argc, char **argv)
{

  event_init();
  //httpd = evhttp_start("0.0.0.0", 8080);

  auto base = event_base_new();
  auto httpd = evhttp_new(base);

  /* Set a callback for requests to "/specific". */
  /* evhttp_set_cb(httpd, "/specific", another_handler, NULL); */


  /* Set a callback for all other requests. */
  evhttp_set_gencb(httpd, generic_handler, NULL);

  auto bound_socket = evhttp_bind_socket_with_handle(httpd, "0.0.0.0", 8080);
  auto fd = evhttp_bound_socket_get_fd(bound_socket);

  event_dispatch();    /* Not reached in this code as it is now. */
  evhttp_free(httpd);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libwebsockets.h>

static int callback_http(struct libwebsocket_context* context,
                         struct libwebsocket* wsi,
                         enum libwebsocket_callback_reasons reason,
                         void *user,
                         void *in, size_t len)
{
  switch (reason) {
    // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/libwebsockets.h#n260
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      printf("connection established\n");

      // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/libwebsockets.h#n281
    case LWS_CALLBACK_HTTP: {
      // auto universal_response = "Hello, World!";
      // libwebsocket_write(wsi, (unsigned char*)universal_response, strlen(universal_response), LWS_WRITE_HTTP);
      // break;
      char *requested_uri = (char *) in;
      printf("requested URI: %s\n", requested_uri);

      if (strcmp(requested_uri, "/") == 0) {
        printf("say hello~\n");
        const char* universal_response = "Hello, World!";
        // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/libwebsockets.h#n597
        libwebsocket_write(wsi, (unsigned char*)universal_response,
                           strlen(universal_response), LWS_WRITE_HTTP);
        break;

      } else {
        // try to get current working directory
        char cwd[1024];
        char *resource_path;

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
          // allocate enough memory for the resource path
          resource_path = (char*)malloc(strlen(cwd) + strlen(requested_uri));

          // join current working direcotry to the resource path
          sprintf(resource_path, "%s%s", cwd, requested_uri);
          printf("resource path: %s\n", resource_path);

          char *extension = strrchr(resource_path, '.');
          char *mime;

          // choose mime type based on the file extension
          if (extension == NULL) {
            mime = "text/plain";
          } else if (strcmp(extension, ".png") == 0) {
            mime = "image/png";
          } else if (strcmp(extension, ".jpg") == 0) {
            mime = "image/jpg";
          } else if (strcmp(extension, ".gif") == 0) {
            mime = "image/gif";
          } else if (strcmp(extension, ".html") == 0) {
            mime = "text/html";
          } else if (strcmp(extension, ".css") == 0) {
            mime = "text/css";
          } else {
            mime = "text/plain";
          }

          // by default non existing resources return code 400
          // for more information how this function handles headers
          // see it's source code
          // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/parsers.c#n1896
          libwebsockets_serve_http_file(context, wsi, resource_path, mime);

        }
      }

      // close connection
      // libwebsocket_close_and_free_session(context, wsi,
      //                                     LWS_CLOSE_STATUS_NORMAL);
      break;
    }

    case LWS_CALLBACK_ESTABLISHED: // just log message that someone is connecting
      printf("connection established\n");
      break;
    case LWS_CALLBACK_RECEIVE: { // the funny part
      // create a buffer to hold our response
      // it has to have some pre and post padding. You don't need to care
      // what comes there, libwebsockets will do everything for you. For more info see
      // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/libwebsockets.h#n597
      unsigned char *buf = (unsigned char*) malloc(LWS_SEND_BUFFER_PRE_PADDING + len +
                                                   LWS_SEND_BUFFER_POST_PADDING);

      int i;

      // pointer to `void *in` holds the incomming request
      // we're just going to put it in reverse order and put it in `buf` with
      // correct offset. `len` holds length of the request.
      for (i=0; i < len; i++) {
        buf[LWS_SEND_BUFFER_PRE_PADDING + (len - 1) - i ] = ((char *) in)[i];
      }

      // log what we recieved and what we're going to send as a response.
      // that disco syntax `%.*s` is used to print just a part of our buffer
      // http://stackoverflow.com/questions/5189071/print-part-of-char-array
      printf("received data: %s, replying: %.*s\n", (char *) in, (int) len,
             buf + LWS_SEND_BUFFER_PRE_PADDING);

      // send response
      // just notice that we have to tell where exactly our response starts. That's
      // why there's `buf[LWS_SEND_BUFFER_PRE_PADDING]` and how long it is.
      // we know that our response has the same length as request because
      // it's the same message in reverse order.
      libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], len, LWS_WRITE_TEXT);

      // release memory back into the wild
      free(buf);
      break;
    }
    default:
      printf("unhandled callback %d\n", reason);
      break;
  }

  return 0;
}



static int callback_dumb_increment(struct libwebsocket_context* context,
                                   struct libwebsocket *wsi,
                                   enum libwebsocket_callback_reasons reason,
                                   void *user, void *in, size_t len)
{

  switch (reason) {
    case LWS_CALLBACK_ESTABLISHED: // just log message that someone is connecting
      printf("connection established\n");
      break;
    case LWS_CALLBACK_RECEIVE: { // the funny part
      // create a buffer to hold our response
      // it has to have some pre and post padding. You don't need to care
      // what comes there, libwebsockets will do everything for you. For more info see
      // http://git.warmcat.com/cgi-bin/cgit/libwebsockets/tree/lib/libwebsockets.h#n597
      unsigned char *buf = (unsigned char*) malloc(LWS_SEND_BUFFER_PRE_PADDING + len +
                                                   LWS_SEND_BUFFER_POST_PADDING);

      int i;

      // pointer to `void *in` holds the incomming request
      // we're just going to put it in reverse order and put it in `buf` with
      // correct offset. `len` holds length of the request.
      for (i=0; i < len; i++) {
        buf[LWS_SEND_BUFFER_PRE_PADDING + (len - 1) - i ] = ((char *) in)[i];
      }

      // log what we recieved and what we're going to send as a response.
      // that disco syntax `%.*s` is used to print just a part of our buffer
      // http://stackoverflow.com/questions/5189071/print-part-of-char-array
      printf("received data: %s, replying: %.*s\n", (char *) in, (int) len,
             buf + LWS_SEND_BUFFER_PRE_PADDING);

      // send response
      // just notice that we have to tell where exactly our response starts. That's
      // why there's `buf[LWS_SEND_BUFFER_PRE_PADDING]` and how long it is.
      // we know that our response has the same length as request because
      // it's the same message in reverse order.
      libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], len, LWS_WRITE_TEXT);

      // release memory back into the wild
      free(buf);
      break;
    }
    default:
      break;
  }


  return 0;
}

static struct libwebsocket_protocols protocols[] = {
  /* first protocol must always be HTTP handler */
  {
    "http-only",   // name
    callback_http, // callback
    0              // per_session_data_size
  },
  {
    "dumb-increment-protocol", // protocol name - very important!
    callback_dumb_increment,   // callback
    0                          // we don't use any per session data

  },
  {
    NULL, NULL, 0   /* End of list */
  }
};


int main(void) {
  int port = 8080;
  const char *interface = NULL;
  struct libwebsocket_context *context;
  int opts = 0;

  struct lws_context_creation_info info;
  memset(&info, 0, sizeof(info));
  
  info.port = port;
  info.iface = interface;
  info.protocols = protocols;
  info.extensions = libwebsocket_get_internal_extensions();
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

  context = libwebsocket_create_context(&info);
  

  if (context == NULL) {
    fprintf(stderr, "libwebsocket init failed\n");
    return -1;
  }

  printf("starting server...\n");

  // infinite loop, to end this server send SIGTERM. (CTRL+C)
  while (1) {
    libwebsocket_service(context, 50);
    // libwebsocket_service will process all waiting events with their
    // callback functions and then wait 50 ms.
    // (this is a single threaded webserver and this will keep our server
    // from generating load while there are not requests to process)
  }

  libwebsocket_context_destroy(context);

  return 0;
}



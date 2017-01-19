#include "render_text.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "graphic/bitmap.h"
#include "graphic/canvas.h"



int main(int argc, char* argv[])
{
  int server_sockfd, client_sockfd;
  int state, client_len;
  pid_t pid;

  struct sockaddr_un clientaddr, serveraddr;

  char buf[255];
  char line[255];

  memset(line, '0', 255);
  state = 0;

  if (access("/tmp/sock1", F_OK) == 0) {
    
  }

  client_len = sizeof(clientaddr);

  if ((server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket error : ");
    exit(0);
  }
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sun_family = AF_UNIX;
  strcpy(serveraddr.sun_path, "/tmp/sock1");


  state = bind(server_sockfd , (struct sockaddr *)&serveraddr,
               sizeof(serveraddr));
  if (state == -1) {
    perror("bind error : ");
    exit(0);
  }

  state = listen(server_sockfd, 5);
  if (state == -1) {
    perror("listen error : ");
    exit(0);
  }

  printf("accept...");
  while(1) {
    client_sockfd = accept(server_sockfd,
                           (struct sockaddr *)&clientaddr,
                           (unsigned int*)&client_len);
    printf("accepted\n");
    pid = fork();
    if (pid == 0) {
      if (client_sockfd == -1) {
        perror("Accept error : ");
        exit(0);
      }

      le::RenderText rendertext;
      
      while(1) {
        memset(buf, 0, 255);
        if (read(client_sockfd, buf, 1) <= 0) {
          close(client_sockfd);
          exit(0);
        }

        printf("recieved : %s\n", buf);

        rendertext.InsertText(std::string(&buf[0]));
        rendertext.Layout();

        auto& document_view = rendertext.GetDocument().GetView();

        auto bitmap = new le::Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);

        std::cout << "painting...";
        le::Canvas canvas;
        canvas.SetBitmap(bitmap);
        rendertext.Paint(canvas);
        std::cout << "complete!" <<std::endl;

        auto data = bitmap->GetData();
        auto size = bitmap->GetWidth() * bitmap->GetHeight() * bitmap->GetDepth();

        // key_t keyval = pid;
        // auto shmid = shmget(keyval,
        //                     size,
        //                     0666 | IPC_CREAT);

        // auto shared_mem = shmat(shmid, (void *)0, 0);
        // memcpy(shared_mem, data, size);

        int buffer_size = sizeof(int) * 3 + size;
        char* buffer = new char[buffer_size];

        std::cout << "buffer size:" <<buffer_size<<std::endl;

        auto bitmap_width = bitmap->GetWidth();
        auto bitmap_height = bitmap->GetHeight();
        auto bitmap_depth = bitmap->GetDepth();

        std::cout << "width..." << bitmap_width << std::endl;
        std::cout << "height..." << bitmap_height << std::endl;
        std::cout << "depth..." << bitmap_depth << std::endl;

        std::cout << "create buffer...";
        
        memcpy(buffer + sizeof(int)*0, &bitmap_width, sizeof(int));
        memcpy(buffer + sizeof(int)*1, &bitmap_height, sizeof(int));
        memcpy(buffer + sizeof(int)*2, &bitmap_depth, sizeof(int));
        memcpy(buffer + sizeof(int)*3, buffer, size);

        std::cout << "complete!" << std::endl;
        std::cout << "writing..." <<std::endl;
        
        write(client_sockfd, buffer, buffer_size);

        delete[] buffer;

        // std::string json =
        //   "{ \"shmkey\":" + std::to_string(keyval) +
        //   ", \"width\":" + std::to_string(bitmap->GetWidth()) +
        //   ", \"height\":" + std::to_string(bitmap->GetHeight()) +
        //   ", \"depth\":" + std::to_string(bitmap->GetDepth()) +
        //   ", \"data\":" + std::to_string(bitmap->GetDepth()) +
        //   "}";
        // write(client_sockfd, json.c_str(), json.size());
      }
    }
  }
  close(client_sockfd);
}

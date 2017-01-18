#include "render_text.h"

#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

struct SocketEvent {
  int type_;
  int data1_;
  int data2_;
};

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

  if (access("/tmp/sock1", F_OK) == 0)
  {
    
  }

  client_len = sizeof(clientaddr);

  if ((server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    perror("socket error : ");
    exit(0);
  }
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sun_family = AF_UNIX;
  strcpy(serveraddr.sun_path, "/tmp/sock1");


  state = bind(server_sockfd , (struct sockaddr *)&serveraddr,
               sizeof(serveraddr));
  if (state == -1)
  {
    perror("bind error : ");
    exit(0);
  }

  state = listen(server_sockfd, 5);
  if (state == -1)
  {
    perror("listen error : ");
    exit(0);
  }


  printf("accept...");
  while(1)
  {
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
        SocketEvent event;
        memset(buf, 0, 255);
        if (read(client_sockfd, buf, 255) <= 0) {
          close(client_sockfd);
          exit(0);
        }

        printf("recieved : %s\n", buf);

        rendertext.InsertText(std::string(&buf[0]));
        rendertext.Layout();
        rendertext.Paint();
        write(client_sockfd, "end", 3);
      }
    }
  }
  close(client_sockfd);
}

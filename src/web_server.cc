#include <png.h>

#include "render_text.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#include "graphic/bitmap.h"
#include "graphic/canvas.h"
#include "controller/event/mouse_event.h"
#include "controller/event/key_event.h"


#include <jsoncpp/json/json.h>

std::string ReadNextJson(int fd)
{
  std::cout << "READ NEXT JSON..." << std::endl;
  std::string json;
  char buf = 0;
  int open = 0;

  
  while( true ) {
    auto sz = read(fd, &buf, sizeof(buf));
    if( sz < 0 )
      exit(0);
    json.push_back(buf);
    if( buf == '{' ) {
      ++open;
    } else if( buf == '}' ) {
      --open;
      if( open == 0 )
        break;
    }
  }

  return json;
}

bool ProcessEvent(const std::string& json, le::RenderText& rendertext)
{

  Json::Value root;
  Json::Reader reader;

  if( !reader.parse(json, root) )
    return false;

  auto event_type = root.get("type", "" ).asString();
  if( event_type == "keypress" ) {
    auto key = root.get("key", "" ).asString();
    std::cout << "received key : " <<key<< std::endl;
    rendertext.InsertText(key);
    rendertext.Layout();
    return true;
  } else if( event_type == "keydown" ) {
    auto code = root.get("keyCode", "" ).asInt();
    auto ctrl = root.get("ctrlKey", "false" ).asBool();
    auto alt = root.get("altKey", "false" ).asBool();
    auto shift = root.get("shiftKey", "false" ).asBool();
    
    le::KeyEvent keyevent;
    auto str = root.get("key", "" ).asString();
    if( str.length() == 1 )
      keyevent.SetChar(str[0]);
    
    keyevent.SetCode(static_cast<le::KeyboardCode>(code));
    keyevent.SetCtrlDown(ctrl);
    keyevent.SetAltDown(alt);
    keyevent.SetShiftDown(shift);
    
    rendertext.OnKeyDown(keyevent);
    rendertext.Layout();
    return true;
    
  } else if ( event_type == "mousedown" ) {
    
    auto x = root.get("x", "0" ).asInt();
    auto y = root.get("y", "0" ).asInt();

    le::MouseEvent event;
    event.SetX(x);
    event.SetY(y);

    rendertext.OnMousePressed(event);
    return false;
  }
  
  
}


void PngWriteCallback(png_structp png_ptr, png_bytep data, png_size_t length) {
  std::vector<char> *p = (std::vector<char>*)png_get_io_ptr(png_ptr);
  p->insert(p->end(), data, data + length);
}


std::vector<char> Buffer2Png(int width, int height, char* buffer)
{
  std::vector<char> out;
  
  png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(p);
  setjmp(png_jmpbuf(p));
  png_set_IHDR(p, info_ptr, width, height, 8,
               PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);


  std::vector<char*> rows(height);
  for (size_t y = 0; y < height; ++y)
    rows[y] = buffer + y * width * 3;

  //png_set_compression_level(p, 1);
  png_set_rows(p, info_ptr, (unsigned char**)&rows[0]);
  png_set_write_fn(p, &out, PngWriteCallback, NULL);

  png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  return out;
}

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
    perror("sock file error : ");
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

        auto json = ReadNextJson(client_sockfd);
        std::cout << "received : "<<json << std::endl;
        if ( !ProcessEvent(json, rendertext) ) {
          continue;
        }
        
        auto& document_view = rendertext.GetDocument().GetView();
        auto bitmap = new le::Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);

        std::cout << "painting...";
        le::Canvas canvas;
        canvas.SetBitmap(bitmap);
        rendertext.Paint(canvas);
        std::cout << "complete!" <<std::endl;

        auto data = bitmap->GetData();
        auto size = bitmap->GetWidth() * bitmap->GetHeight() * bitmap->GetDepth();

        // bitmap->WriteBitmapFile("output.bmp");

        auto bitmap_width = bitmap->GetWidth();
        auto bitmap_height = bitmap->GetHeight();
        auto bitmap_depth = bitmap->GetDepth();

        std::cout << "compress...";
        auto out = Buffer2Png(bitmap_width, bitmap_height, (char*)data);
        std::cout << "bufferlen:" <<out.size() << "complete!" <<std::endl;
        
        std::cout << "writing...";
        write(client_sockfd, out.data(), out.size());

        // std::ofstream outfile("output.png", std::ios::out);
        // outfile.write(out.data(), out.size());
        
        std::cout << "complete!" <<std::endl;
      }
    }
  }
  close(client_sockfd);
}

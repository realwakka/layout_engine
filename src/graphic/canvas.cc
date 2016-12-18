#include "canvas.h"

#include <cstring>
#include <fstream>
#include "model/glyph/glyph.h"

namespace le {

namespace {

void writeBitmap(const std::string& filename, int w, int h, const char* img) {
  
  FILE *f;
  int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(       w    );
  bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
  bmpinfoheader[ 6] = (unsigned char)(       w>>16);
  bmpinfoheader[ 7] = (unsigned char)(       w>>24);
  bmpinfoheader[ 8] = (unsigned char)(       h    );
  bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
  bmpinfoheader[10] = (unsigned char)(       h>>16);
  bmpinfoheader[11] = (unsigned char)(       h>>24);

  f = fopen(filename.c_str(),"wb");
  fwrite(bmpfileheader,1,14,f);
  fwrite(bmpinfoheader,1,40,f);
  for(int i=0; i<h; i++)
  {
    fwrite(img+(w*(h-i-1)*3),3,w,f);
    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
  }
  fclose(f);
}

}

const int kWidth = 500;
const int kHeight = 500;

Canvas::Canvas()
    : buffer_( new char[kWidth * kHeight * 3] )
{
  matrix_stack_.push(Matrix());
}

Canvas::~Canvas()
{
}

void Canvas::DrawGlyph(int x, int y, const Glyph& glyph)
{
  auto buffer = glyph.GetBitmapBuffer();
  for( int j=0 ; j<glyph.GetBitmapHeight() ; ++j ) {
    for( int i=0 ; i<glyph.GetBitmapWidth() ; ++i ) {
      auto val = buffer[j * glyph.GetBitmapWidth() + i];
      SetPixel(x + i, y + j, val);
    }
  }
}

void Canvas::Save()
{
  matrix_stack_.push(matrix_stack_.top());
}
void Canvas::Restore()
{
  matrix_stack_.pop();
}

void Canvas::SetPixel(int x, int y, int color)
{
  int width = 500;
  int address = ( y * width + x ) * 3;
  std::memcpy( &buffer_[address], &color, sizeof(color) );
}

void Canvas::WriteRaw(const std::string filename)
{
  std::ofstream outfile (filename,std::ofstream::binary);
  outfile.write(buffer_, kWidth * kHeight * 3);
  
  outfile.close();

  
}

void Canvas::WriteBitmap(const std::string filename)
{
  writeBitmap(filename, kWidth, kHeight, buffer_ );
}

}  // le

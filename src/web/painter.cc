#include "painter.h"

#include <iostream>
#include <png.h>

#include "graphic/bitmap.h"
#include "graphic/bitmap_canvas.h"

#include "render_text.h"

namespace le {
namespace web {

namespace {

void PngWriteCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
  std::vector<char> *p = (std::vector<char>*)png_get_io_ptr(png_ptr);
  p->insert(p->end(), data, data + length);
}

std::vector<unsigned char> Buffer2Png(int width, int height, unsigned char* buffer)
{
  std::vector<unsigned char> out;
  
  png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(p);
  setjmp(png_jmpbuf(p));
  png_set_IHDR(p, info_ptr, width, height, 8,
               PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);


  std::vector<unsigned char*> rows(height);
  for (size_t y = 0; y < height; ++y)
    rows[y] = buffer + y * width * 3;

  //png_set_compression_level(p, 1);
  png_set_rows(p, info_ptr, (unsigned char**)&rows[0]);
  png_set_write_fn(p, &out, PngWriteCallback, NULL);

  png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  return out;
}


}

Painter::Painter()
{}

Painter::~Painter()
{}

std::vector<unsigned char> Painter::PaintToPng(RenderText& rendertext)
{
  auto&& document_view = rendertext.GetDocument().GetView();
  auto bitmap = new le::Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);
  
  le::BitmapCanvas canvas;
  canvas.SetBitmap(bitmap);
  rendertext.Paint(canvas);
  std::cout << "complete!" <<std::endl;

  auto data = bitmap->GetData();
  auto size = bitmap->GetWidth() * bitmap->GetHeight() * bitmap->GetDepth();

  // bitmap->WriteBitmapFile("output.bmp");

  auto bitmap_width = bitmap->GetWidth();
  auto bitmap_height = bitmap->GetHeight();
  auto bitmap_depth = bitmap->GetDepth();

  auto out = Buffer2Png(bitmap_width, bitmap_height, const_cast<unsigned char*>(data));
  
  return out;
}


}  // web
}  // le

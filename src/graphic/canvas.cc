#include "canvas.h"

#include <cstring>
#include <fstream>
#include "model/glyph/glyph.h"

namespace le {


const int kWidth = 500;
const int kHeight = 500;

Canvas::Canvas()
    : bitmap_( kWidth, kHeight, 3 )
{
  matrix_stack_.push(Matrix());
}

Canvas::~Canvas()
{
}

void Canvas::DrawGlyph(const Point& point, const Glyph& glyph)
{
  auto x = point.GetX();
  auto y = point.GetY();
  auto buffer = glyph.GetBitmapBuffer();
  
  for( int j=0 ; j<glyph.GetBitmapHeight() ; ++j ) {
    for( int i=0 ; i<glyph.GetBitmapWidth() ; ++i ) {
      auto val = buffer[j * glyph.GetBitmapWidth() + i];
      SetPixel(Point(x + i, y + j), val);
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

void Canvas::SetPixel(const Point& point, int color)
{
  auto transformed = point.Transform(GetMatrix());
  bitmap_.SetPixel(transformed.GetX(), transformed.GetY(), color);
}

void Canvas::WriteBitmap(const std::string filename)
{
  bitmap_.WriteBitmapFile(filename);
}

}  // le

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

  auto spanlist = glyph.GetSpanList();
  if( spanlist.empty() )
    return;
  
  auto height = spanlist.back().GetY();

  for( auto&& span : spanlist ) {
    //auto color = SetColorCoverage(glyph.GetColor(), span.GetCoverage());

    auto tmp = span.GetCoverage();
    auto color = SetARGB(tmp, 255, 0, 0);
    
    for( int i=0 ; i<span.GetLength() ; ++i ) {
      SetPixel(Point(span.GetX() + x + i, (y - span.GetY())), color);
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

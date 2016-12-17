#include "canvas.h"

#include <cstring>
#include "model/glyph/glyph.h"

namespace le {

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::DrawGlyph(int x, int y, const Glyph& glyph)
{
  auto buffer = glyph.GetBitmapBuffer();
  for( int j=0 ; j<glyph.GetBitmapHeight() ; ++j ) {
    for( int i=0 ; i<glyph.GetBitmapWidth() ; ++i ) {
      SetPixel(x, y, 0);
    }
  }
}
void Canvas::Save()
{
  matrix_stack_.push(Matrix());
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


}  // le

#include "canvas.h"

namespace le {

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::DrawGlyph(int x, int y, const Glyph& glyph)
{
  
}
void Canvas::Save()
{
  matrix_stack_.push(Matrix());
}
void Canvas::Restore()
{
  matrix_stack_.pop();
}


}  // le

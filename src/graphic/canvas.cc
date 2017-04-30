#include "canvas.h"

#include <cmath>
#include <cstring>
#include <fstream>
#include "model/glyph/glyph.h"
#include "graphic/paint.h"

namespace le {

Canvas::Canvas()
{
  matrix_stack_.push(Matrix());
}

Canvas::~Canvas()
{
}

void Canvas::Save()
{
  matrix_stack_.push(matrix_stack_.top());
}
void Canvas::Restore()
{
  matrix_stack_.pop();
}

}  // le

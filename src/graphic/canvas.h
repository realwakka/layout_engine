#ifndef CANVAS_H_
#define CANVAS_H_

#include "point.h"
#include "matrix.h"
#include <stack>

namespace le {

class Glyph;

class Canvas
{
 public:
  Canvas();
  virtual ~Canvas();

 public:
  void DrawGlyph(int x, int y, const Glyph& glyph);
  void Save();
  void Restore();
  void SetPixel(int x, int y, int color);

 private:
  char* buffer_;
  std::stack<Matrix> matrix_stack_;
  
};


}  // le

#endif /* CANVAS_H_ */


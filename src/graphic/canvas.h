#ifndef CANVAS_H_
#define CANVAS_H_

#include "point.h"
#include "matrix.h"
#include "bitmap.h"
#include <stack>
#include <string>
#include <memory>


namespace le {

class Glyph;
class Paint;

class Canvas
{
 public:
  Canvas();
  virtual ~Canvas();
  
  virtual void DrawRect(const Point& p1, const Point& p2, const Paint& paint) = 0;
  virtual void DrawGlyph(const Point& point, const Glyph& glyph) = 0;
  void Save();
  void Restore();
  virtual void SetPixel(const Point& point, int color) = 0;
  virtual void DrawLine(const Point& p1, const Point& p2, const Paint& paint) = 0;

  Matrix& GetMatrix() { matrix_stack_.top(); }
  
 private:
  std::stack<Matrix> matrix_stack_;
  
};

}  // le

#endif /* CANVAS_H_ */


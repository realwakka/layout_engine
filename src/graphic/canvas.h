#ifndef CANVAS_H_
#define CANVAS_H_

#include "point.h"
#include "matrix.h"
#include "bitmap.h"
#include <stack>
#include <string>


namespace le {

class Glyph;

class Canvas
{
 public:
  Canvas();
  virtual ~Canvas();

 public:
  void DrawRect(const Point& p1, const Point& p2, Color color);
  void DrawGlyph(const Point& point, const Glyph& glyph);
  void Save();
  void Restore();
  void SetPixel(const Point& point, int color);
  void WriteBitmap(const std::string filename);

  Matrix& GetMatrix() { matrix_stack_.top(); }

 private:
  //char* buffer_;
  Bitmap bitmap_;
  std::stack<Matrix> matrix_stack_;
  
};


}  // le

#endif /* CANVAS_H_ */


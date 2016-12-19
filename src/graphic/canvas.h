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
  // void DrawGlyph(int x, int y, const Glyph& glyph);
  void DrawGlyph(const Point& point, const Glyph& glyph);
  void Save();
  void Restore();
  // void SetPixel(int x, int y, int color);
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


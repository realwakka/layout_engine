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

 public:
  void DrawRect(const Point& p1, const Point& p2, const Paint& paint);
  void DrawGlyph(const Point& point, const Glyph& glyph);
  void Save();
  void Restore();
  void SetPixel(const Point& point, int color);
  void WriteBitmap(const std::string filename);
  void DrawLine(const Point& p1, const Point& p2, const Paint& paint);

  Matrix& GetMatrix() { matrix_stack_.top(); }

  void SetBitmap(Bitmap* bitmap) { bitmap_.reset(bitmap); }

 private:
  //char* buffer_;
  std::unique_ptr<Bitmap> bitmap_;
  std::stack<Matrix> matrix_stack_;
  
};


}  // le

#endif /* CANVAS_H_ */


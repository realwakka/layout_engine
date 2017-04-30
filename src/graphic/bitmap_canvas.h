#ifndef LE_GRAPHIC_BITMAP_CANVAS_H_
#define LE_GRAPHIC_BITMAP_CANVAS_H_

#include "graphic/canvas.h"

namespace le {

class BitmapCanvas : public Canvas
{
public:
  BitmapCanvas();
  virtual ~BitmapCanvas();

  void DrawRect(const Point& p1, const Point& p2, const Paint& paint) override;
  void DrawGlyph(const Point& point, const Glyph& glyph) override;
  void DrawLine(const Point& p1, const Point& p2, const Paint& paint) override;
  void SetPixel(const Point& point, int color) override;
  
  void WriteBitmap(const std::string filename);
  void SetBitmap(Bitmap* bitmap) { bitmap_.reset(bitmap); }
  
 private:
  std::unique_ptr<Bitmap> bitmap_;
  
};
  

}  // le

#endif /* LE_GRAPHIC_BITMAP_CANVAS_H_ */

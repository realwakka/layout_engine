#ifndef LE_SVG_CANVAS_H_
#define LE_SVG_CANVAS_H_

#include "graphic/canvas.h"

namespace le {

class SvgCanvas : public Canvas
{
 public:
  SvgCanvas();
  virtual ~SvgCanvas();

  void DrawRect(const Point& p1, const Point& p2, const Paint& paint) override;
  void DrawGlyph(const Point& point, const Glyph& glyph) override;
  void SetPixel(const Point& point, int color) override;
  void DrawLine(const Point& p1, const Point& p2, const Paint& paint) override;

};


}  // le

#endif /* LE_SVG_CANVAS_H_ */

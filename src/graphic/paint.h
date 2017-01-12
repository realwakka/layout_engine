#ifndef LE_PAINT_H_
#define LE_PAINT_H_

#include "graphic/color.h"

namespace le {

class Paint
{
 public:
  enum class Style {
    kFill,
      kStroke,
      kStrokeAndFill
  };
  
 public:
  Paint();
  virtual ~Paint();

  Color GetColor() const { return color_; }
  void SetColor(Color color) { color_ = color; }
  
  int GetStrokeWidth() const { return stroke_width_; }
  void SetStrokeWidth(int stroke_width) { stroke_width_ = stroke_width; }

  Style GetStyle() const { return style_; }
  void SetStyle(Style style) { style_ = style; }
  
 private:
  Color color_;
  int stroke_width_;
  Style style_;
};


}  // le

#endif /* LE_PAINT_H_ */

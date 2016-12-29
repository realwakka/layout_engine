#ifndef RUNPROP_H_
#define RUNPROP_H_

#include "model/face/face.h"
#include "model/prop/font.h"
#include "graphic/color.h"

namespace le {

class RunProp
{
 public:
  RunProp();
  virtual ~RunProp();

  int GetSize() const { return size_; }
  void SetSize(int size) { size_ = size; }

  Color GetColor() const { return color_; }
  void SetColor(Color color) { color_ = color; }

  bool GetBold() const { return bold_; }
  void SetBold(bool bold) { bold_ = bold; }

  bool GetItalic() const { return italic_; }
  void SetItalic(bool italic) { italic_ = italic; }

 private:
  int size_;
  Font font_;
  Color color_;

  bool italic_;
  bool bold_;
  
  
};


}  // le

#endif /* RUNPROP_H_ */

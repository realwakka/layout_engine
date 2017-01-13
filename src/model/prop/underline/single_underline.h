#ifndef LE_SINGLE_UNDERLINE_H_
#define LE_SINGLE_UNDERLINE_H_

#include "model/prop/underline/underline.h"

namespace le {

class SingleUnderline : public Underline
{
 public:
  SingleUnderline();
  virtual ~SingleUnderline();
  
  void DrawUnderline(const RunView& runview, Canvas& canvas) override;
};


}  // le

#endif /* LE_SINGLE_UNDERLINE_H_ */

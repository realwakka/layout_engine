#ifndef UNDERLINE_H_
#define UNDERLINE_H_

namespace le {

class RunView;
class Canvas;

class Underline
{
 public:
  virtual void DrawUnderline(const RunView& runview, Canvas& canvas) = 0;
};


}  // le

#endif /* UNDERLINE_H_ */


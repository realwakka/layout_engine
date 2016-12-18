#ifndef LE_PARAGRAPH_VIEW_H_
#define LE_PARAGRAPH_VIEW_H_

#include <vector>
#include "view/view.h"

namespace le {

class LineView;
class Paragraph;

class ParagraphView : public View
{
 public:
  ParagraphView(Paragraph& paragraph);
  virtual ~ParagraphView();

  virtual void Paint(Canvas& canvas) override;
  virtual void Layout() override;
  
 private:
  Paragraph& paragraph_;
};


}  // le

#endif /* LE_PARAGRAPH_VIEW_H_ */

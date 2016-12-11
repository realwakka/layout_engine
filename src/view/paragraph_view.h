#ifndef LE_PARAGRAPH_VIEW_H_
#define LE_PARAGRAPH_VIEW_H_

#include <vector>

namespace le {

class LineView;
class Paragraph;

class ParagraphView
{
 public:
  ParagraphView(Paragraph& paragraph);
  virtual ~ParagraphView();
  
 private:
  std::vector<LineView*> line_views_;
  Paragraph& paragraph_;
};


}  // le

#endif /* LE_PARAGRAPH_VIEW_H_ */

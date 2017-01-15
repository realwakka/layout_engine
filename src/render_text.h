#ifndef LE_RENDER_TEXT_H_
#define LE_RENDER_TEXT_H_

#include "model/document.h"
#include "model/selection/selection.h"

namespace le {

class RenderText
{
 public:
  RenderText();
  virtual ~RenderText();

  void InsertText(const std::string& text);
  void SetBold(bool bold);
  void SetItalic(bool italic);
  void SetSize(int size);
  void Layout();
  void Paint();
  
 private:
  Document document_;
  std::unique_ptr<Selection> selection_;

};


}  // le

#endif /* LE_RENDER_TEXT_H_ */

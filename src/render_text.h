#ifndef LE_RENDER_TEXT_H_
#define LE_RENDER_TEXT_H_

#include "controller/paragraph_controller.h"
#include "model/document.h"

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
  ParagraphController controller_;
  Document document_;

};


}  // le

#endif /* LE_RENDER_TEXT_H_ */

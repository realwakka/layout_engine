#ifndef LE_RENDER_TEXT_H_
#define LE_RENDER_TEXT_H_

#include "model/document.h"
#include "model/selection/selection.h"

namespace le {

class MouseEvent;
class KeyEvent;

class RenderText
{
 public:
  RenderText();
  virtual ~RenderText();

  void InsertText(const std::string& text);
  void BackSpace();
  void SetBold(bool bold);
  void SetItalic(bool italic);
  void SetSize(int size);
  void Layout();
  void Paint(Canvas& canvas);
  void SetPageSize(int width, int height);
  void WriteBitmapFile(std::string path);

  void OnMousePressed(const MouseEvent& event);
  void OnKeyDown(const KeyEvent& event);
  Document& GetDocument() { return document_; }

  void Commit();
  void UnDo();
  void ReDo();
  
 private:
  Document document_;
  std::unique_ptr<Selection> selection_;

};


}  // le

#endif /* LE_RENDER_TEXT_H_ */

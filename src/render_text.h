#ifndef LE_RENDER_TEXT_H_
#define LE_RENDER_TEXT_H_

#include <memory>

#include "model/document.h"
#include "model/selection/selection.h"
#include "controller/command/commit_tree.h"

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

  void SetSelection(std::shared_ptr<Selection> selection) { selection_ = selection; }
  std::shared_ptr<Selection> GetSelection() { return selection_; }
  
  
  void Commit();
  void UnDo();
  void ReDo();

  CommitTree* GetCommitTree() { return &commit_tree_; }

  Run* GetCachedRun() { return cached_run_; }
  void SetCachedRun(Run* cached_run){ cached_run_ =  cached_run; }
  
 private:
  Document document_;
  std::shared_ptr<Selection> selection_;
  CommitTree commit_tree_;

  Run* cached_run_;

};


}  // le

#endif /* LE_RENDER_TEXT_H_ */

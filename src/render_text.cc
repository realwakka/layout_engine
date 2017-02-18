#include "render_text.h"
#include "graphic/canvas.h"

#include "model/selection/selection.h"
#include "model/selection/caret_selection.h"
#include "model/character/character.h"
#include "controller/controller.h"
#include "controller/command/commit_tree.h"

namespace le {

RenderText::RenderText()
    : document_(this)
{
  selection_ = new CaretSelection(*document_.GetFirstChild()->GetEnterRun()->GetEnterChar());
}

RenderText::~RenderText()
{}

void RenderText::InsertText(const std::string& text)
{
  for( char c : text ) {
    auto character = CreateCharacter(c);
    selection_->GetController(this)->InsertChar(character);
    //paragraph_.PrintInfo();
  }
  //paragraph_.GetFirstRun()->UpdateGlyph();
}

void RenderText::SetBold(bool bold)
{
  selection_->GetController(this)->SetBold(bold);
}

void RenderText::SetItalic(bool italic)
{
  selection_->GetController(this)->SetItalic(italic);
}

void RenderText::SetSize(int size)
{
  selection_->GetController(this)->SetSize(size);
}

void RenderText::SetPageSize(int width, int height)
{
  
}

void RenderText::Commit()
{
  commit_tree_.DoCommit();
}

void RenderText::Layout()
{
  document_.GetView().Layout();
  selection_->GetView().Layout();
}

void RenderText::Paint(Canvas& canvas)
{
  auto& document_view = document_.GetView();
  document_.GetView().Paint(canvas);
  selection_->GetView().Paint(canvas);
}

void RenderText::WriteBitmapFile(std::string path)
{
  Canvas canvas;
  auto& document_view = document_.GetView();
  auto bitmap = new Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);
  canvas.SetBitmap(bitmap);
  document_.GetView().Paint(canvas);
  selection_->GetView().Paint(canvas);
  canvas.WriteBitmap(path);
}

void RenderText::OnMousePressed(const MouseEvent& event)
{
  selection_->GetController(this)->OnMousePressed(event);
}

void RenderText::BackSpace()
{
  selection_->GetController(this)->BackSpaceChar();
}

void RenderText::UnDo()
{
  commit_tree_.UnDo();
}

void RenderText::ReDo()
{

  commit_tree_.ReDo();
}


void RenderText::OnKeyDown(const KeyEvent& event)
{
  selection_->GetController(this)->OnKeyDown(event);
}


}  // le

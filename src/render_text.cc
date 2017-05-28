#include "render_text.h"
#include "graphic/bitmap_canvas.h"

#include "model/selection/selection.h"
#include "model/selection/caret_selection.h"
#include "model/character/character.h"
#include "controller/controller.h"
#include "controller/caret_controller.h"
#include "controller/command/commit_tree.h"

namespace le {

RenderText::RenderText()
  : document_(this),
    cached_run_(nullptr)
{
  auto character = document_.GetFirstChild()->GetEnterRun()->GetEnterChar();
  controller_ = std::make_shared<CaretController>(*character, this);
}

RenderText::~RenderText()
{}

void RenderText::InsertText(const std::string& text)
{
  for( auto c : text ) {
    auto character = CreateCharacter(c);
    controller_->InsertChar(character);
  }
}

void RenderText::SetBold(bool bold)
{
  controller_->SetBold(bold);
}

void RenderText::SetItalic(bool italic)
{
  controller_->SetItalic(italic);
}

void RenderText::SetSize(int size)
{
  controller_->SetSize(size);
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
  controller_->Layout();
}

void RenderText::Paint(Canvas& canvas)
{
  auto& document_view = document_.GetView();
  document_.GetView().Paint(canvas);
  controller_->Paint(canvas);
}

void RenderText::WriteBitmapFile(std::string path)
{
  // BitmapCanvas canvas;
  // auto& document_view = document_.GetView();
  // auto bitmap = new Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);
  // canvas.SetBitmap(bitmap);
  // document_.GetView().Paint(canvas);
  // selection_->GetView().Paint(canvas);
  // canvas.WriteBitmap(path);
}

void RenderText::OnMousePressed(const MouseEvent& event)
{
  controller_->OnMousePressed(event);
}

void RenderText::BackSpace()
{
  controller_->BackSpaceChar();
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
  controller_->OnKeyDown(event);
}


}  // le

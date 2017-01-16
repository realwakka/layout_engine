#include "render_text.h"
#include "graphic/canvas.h"

#include "model/selection/selection.h"
#include "model/selection/caret_selection.h"
#include "model/character/character.h"
#include "controller/controller.h"

namespace le {

RenderText::RenderText()
{
  auto selection = new CaretSelection(*document_.GetFirstChild()->GetEnterRun()->GetEnterChar());
  selection_.reset(selection);
}

RenderText::~RenderText()
{}

void RenderText::InsertText(const std::string& text)
{
  for( char c : text ) {
    auto character = CreateCharacter(c);
    selection_->GetController()->InsertChar(character);
    //paragraph_.PrintInfo();
  }
  //paragraph_.GetFirstRun()->UpdateGlyph();
}

void RenderText::SetBold(bool bold)
{
  selection_->GetController()->SetBold(bold);
}

void RenderText::SetItalic(bool italic)
{
  selection_->GetController()->SetItalic(italic);
}

void RenderText::SetSize(int size)
{
  selection_->GetController()->SetSize(size);
}


void RenderText::Layout()
{
  document_.GetView().Layout();
  selection_->GetView().Layout();
}

void RenderText::Paint()
{
  Canvas canvas;
  auto& document_view = document_.GetView();
  auto bitmap = new Bitmap(document_view.GetWidth(), document_view.GetHeight(), 3);
  canvas.SetBitmap(bitmap);
  document_.GetView().Paint(canvas);
  selection_->GetView().Paint(canvas);
  canvas.WriteBitmap("output.bmp");
}


}  // le

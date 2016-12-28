#include "render_text.h"
#include "graphic/canvas.h"

namespace le {

RenderText::RenderText()
{}

RenderText::~RenderText()
{}

void RenderText::InsertText(const std::string& text)
{
  controller_.InsertText(text);
}

void RenderText::SetBold(bool bold)
{
  controller_.SetBold(bold);
}

void RenderText::SetItalic(bool italic)
{
  controller_.SetItalic(italic);
}

void RenderText::SetSize(int size)
{
  controller_.SetSize(size);
}


void RenderText::Layout()
{
  controller_.Layout();
}

void RenderText::Paint()
{
  Canvas canvas;
  controller_.GetParagraph().GetView().Paint(canvas);
  canvas.WriteBitmap("output.bmp");
}


}  // le

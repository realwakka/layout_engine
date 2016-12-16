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

void RenderText::Layout()
{
  controller_.Layout();
}

void RenderText::Paint()
{
  Canvas canvas;
  controller_.GetParagraph().GetView().Paint(canvas);
}


}  // le

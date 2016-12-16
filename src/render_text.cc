#include "render_text.h"

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


}  // le

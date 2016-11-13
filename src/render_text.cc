#include "render_text.h"

namespace le {

RenderText::RenderText()
{}

RenderText::~RenderText()
{}

void RenderText::insertText(const std::string& text)
{
  controller_.insertText(text);
}


}  // le

#include "paragraph_controller.h"

#include "model/text_run.h"
#include "model/character.h"

namespace le {

ParagraphController::ParagraphController()
{

}

ParagraphController::~ParagraphController()
{

}

void ParagraphController::insertText(std::string text)
{
  auto text_run = new TextRun(text);
  selected_char_->GetTextRun();
}

}  // tmaxoffice

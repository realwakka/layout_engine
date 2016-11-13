#include "paragraph_controller.h"

#include "model/text_run.h"

namespace le {

ParagraphController::ParagraphController()
{

}

ParagraphController::~ParagraphController()
{

}

void ParagraphController::insertText(std::string text)
{
  auto text_run = new TextRun();
  selected_run_->insertRun(text_run);
}

}  // tmaxoffice

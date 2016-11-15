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
    auto run = new TextRun();
    run->
    selected_->insertRun(text_run);
}

}  // tmaxoffice

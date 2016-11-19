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
  for( char c : text ) {
    auto character = new Character(c);
    selected_char_->InsertChar(character);
  }
}

}  // tmaxoffice

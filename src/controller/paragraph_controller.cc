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
    auto run = selected_char_->GetTextRun();
    auto word = selected_char_->GetWord();
    
    
  }
  
  auto text_run = new TextRun(text);
  selected_char_->GetTextRun();

  
}

}  // tmaxoffice

#include "paragraph_controller.h"

#include "model/text_run.h"
#include "model/character/character.h"
#include "model/character/space_character.h"

namespace le {

namespace {

Character* createCharacter(char ch)
{
  switch(ch) {
    case ' ':
      return new SpaceCharacter();
    default:
      return new Character(ch);
  }
}

}

ParagraphController::ParagraphController()
    : selected_char_(paragraph_.GetEnterRun()->GetEnterChar())
{

}

ParagraphController::~ParagraphController()
{

}

void ParagraphController::insertText(std::string text)
{
  for( char c : text ) {
    auto character = createCharacter(c);
    selected_char_->InsertChar(character);
    paragraph_.PrintInfo();
  }
}



}  // tmaxoffice

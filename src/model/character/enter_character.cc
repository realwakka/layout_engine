#include "enter_character.h"

#include "model/word.h"
#include "space_character.h"
#include "model/run.h"
#include "model/paragraph.h"
#include <typeinfo>

namespace le {

EnterCharacter::EnterCharacter(EnterRun* enter_run_)
    : Character('\n')
{
  SetRun(enter_run_);
}

EnterCharacter::~EnterCharacter()
{}

void EnterCharacter::InsertChar(Character* character)
{
  auto paragraph = GetRun()->GetParagraph();
  auto last_word = paragraph->GetLastWord();
  auto last_run =  paragraph->GetLastRun();
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);
    last_word->InsertCharacter(character, nullptr);

    last_run = new Run();
    paragraph->InsertRun(last_run, nullptr);
    last_run->InsertCharacter(character, nullptr);

  }
  else {
    auto prev_char = last_word->GetLastCharacter();
    if( typeid(*character) == typeid(Character) ) {
      if( typeid(*prev_char) == typeid(Character) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
    } else if (typeid(*character) == typeid(SpaceCharacter) ) {
      if( typeid(*prev_char) == typeid(Character) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
      
    } else {

    }
  }
}


}  // le

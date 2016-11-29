#include "enter_character.h"

#include "model/word.h"
#include "space_character.h"
#include "model/run.h"
#include "model/paragraph.h"
#include <typeinfo>

namespace le {

EnterCharacter::EnterCharacter()
    : Character('\n')
{}

EnterCharacter::~EnterCharacter()
{}

void EnterCharacter::InsertChar(Character* character)
{
  auto paragraph = GetRun()->GetParagraph();
  auto last_word = paragraph->GetLastWord();
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);

    auto new_run = new Run();
    paragraph->InsertRun(new_run, nullptr);
  }

  
  // if( typeid(*character) == typeid(Character) ) {

  //   last_word->InsertBefore(character, nullptr);
  // }
  // else if( typeid(*character) == typeid(SpaceCharacter) ) {
  //   if( !prev_char ) {
  //     GetWord()->InsertBefore(character, this);
  //     GetWord()->Split(this);
  //   }
  //   else if( typeid(*prev_char) == typeid(Character) ) {
  //     GetWord()->InsertBefore(character, this);
  //     GetWord()->Split(this);
  //   }
  //   else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
  //     prev_char->GetWord()->InsertBefore(character, nullptr);
  //   }
  // }
  // else {
    
  // }

}


}  // le

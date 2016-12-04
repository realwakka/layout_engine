#include "enter_character.h"

#include "model/word.h"
#include "space_character.h"
#include "model/text_run.h"
#include "model/paragraph.h"
#include <typeinfo>

namespace le {

void InsertWordInternal(Paragraph* paragraph, Character* character)
{
  auto last_word = paragraph->GetLastWord();
  
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);
    last_word->InsertCharacter(character, nullptr);
  } else {
    
    auto prev_char = last_word->GetLastCharacter();
    if( typeid(*character) == typeid(Character) ) {
      if( typeid(*prev_char) == typeid(Character) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if ( typeid(*prev_char) == typeid(SpaceCharacter) ) {
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

void InsertRunInternal(Paragraph* paragraph, Character* character)
{
  auto last_run =  paragraph->GetLastRun();

  if(last_run == nullptr) {
    last_run = new TextRun();
    paragraph->InsertRun(last_run, nullptr);
  }
  
  last_run->InsertCharacter(character, nullptr);
}

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

  InsertWordInternal(paragraph, character);
  InsertRunInternal(paragraph, character);

  
}


}  // le

#include "enter_character.h"

namespace le {

EnterCharacter::EnterCharacter()
    : Character('\n')
{}

EnterCharacter::~EnterCharacter()
{}

void EnterCharacter::InsertChar(Character* character)
{
  auto prev_char = GetPrevChar();
  if( typeid(*character) == typeid(Character) ) {
    GetWord()->InsertBefore(character, this);
  }
  else if( typeid(*character) == typeid(SpaceCharacter) ) {
    if( !prev_char ) {
      GetWord()->InsertBefore(character, this);
      GetWord()->Split(this);
    }
    else if( typeid(*prev_char) == typeid(Character) ) {
      GetWord()->InsertBefore(character, this);
      GetWord()->Split(this);
    }
    else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
      prev_char->GetWord()->InsertBefore(character, nullptr);
    }
  }
  else {
    
  }

}


}  // le

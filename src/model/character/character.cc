#include "character.h"

#include "model/run.h"
#include "model/word.h"

#include "model/character/space_character.h"

namespace le {

Character::Character(char c)
        : c_(c)
{}

Character::~Character()
{}

void Character::InsertChar(Character* character)
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

Character* Character::GetPrevChar()
{
  return nullptr;
}

}  // le

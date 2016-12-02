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
  auto prev_char = GetPrevCharacter();
  if( typeid(*character) == typeid(Character) ) {
    GetWord()->InsertCharacter(character, this);
  }
  else if( typeid(*character) == typeid(SpaceCharacter) ) {
    if( !prev_char ) {
      GetWord()->InsertCharacter(character, this);
      GetWord()->Split(this);
    }
    else if( typeid(*prev_char) == typeid(Character) ) {
      GetWord()->InsertCharacter(character, this);
      GetWord()->Split(this);
    }
    else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
      prev_char->GetWord()->InsertCharacter(character, nullptr);
    }
  }
  else {
    
  }
}

Character* Character::GetPrevCharacter()
{
  if( word_node_.GetContainer()->GetFirstCharacter() == this )
    return this;
  else 
    return *word_node_.GetPrev();
}
Character* Character::GetNextCharacter()
{
  if( word_node_.GetContainer()->GetLastCharacter() == this )
    return this;
  else 
    return *word_node_.GetNext();
}


}  // le

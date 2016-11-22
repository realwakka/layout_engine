#include "character.h"

#include "model/run.h"
#include "model/word.h"

namespace le {

Character::Character(char c)
        : c_(c)
{}

Character::~Character()
{}

void Character::InsertChar(Character* character)
{
  // insert word
  if( GetPrevChar()->GetChar() == ' ' ) {
    //no split
  }
  else {
    if( character->GetChar() == ' ' ) {
      //split
    }
    else {
      //no split
    }
  }

  // insert run
    
  run_->InsertBefore(character, this);
  word_->InsertBefore(character, this);
}


}  // le

#include "space_character.h"

#include "model/word.h"

namespace le {

SpaceCharacter::SpaceCharacter()
    : Character(' ')
{}

SpaceCharacter::~SpaceCharacter()
{}

void SpaceCharacter::InsertChar(Character* character)
{
  if( character->GetChar() == ' ' ) {
    GetWord()->InsertCharacter( character, this );
  }
  else {
    if( GetPrevChar()->GetChar() == ' ' ) {
      // split
      
    }
    else {
      // no split
      GetWord()->InsertCharacter( character, this );
    }
  }

}




}  // le

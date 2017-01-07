#include "space_character.h"

#include "model/word.h"

namespace le {

SpaceCharacter::SpaceCharacter()
    : Character(' '),
      view_(*this)
{}

SpaceCharacter::~SpaceCharacter()
{}



}  // le

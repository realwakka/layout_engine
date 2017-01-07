#include "basic_character.h"

namespace le {

BasicCharacter::BasicCharacter(char c)
    : Character(c),
      view_(*this)
{}

BasicCharacter::~BasicCharacter()
{}


}  // le

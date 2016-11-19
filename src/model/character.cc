#include "character.h"

namespace le {

Character::Character(char c)
        : c_(c)
{}

Character::~Character()
{}

void Character::InsertChar(Character* character)
{
  run_->insertBefore(character, this);
  word_->insertBefore(character, this);

}


}  // le

#include "character.h"

#include "run.h"
#include "word.h"

namespace le {

Character::Character(char c)
        : c_(c)
{}

Character::~Character()
{}

void Character::InsertChar(Character* character)
{
  run_->InsertBefore(character, this);
  word_->InsertBefore(character, this);
}


}  // le

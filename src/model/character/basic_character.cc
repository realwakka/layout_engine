#include "basic_character.h"

namespace le {

BasicCharacter::BasicCharacter(char c)
    : Character(c),
      view_(*this)
{}

BasicCharacter::~BasicCharacter()
{}

void BasicCharacter::InsertChar(Character* character)
{
  
}

void BasicCharacter::SetBold(bool bold)
{

}

void BasicCharacter::SetItalic(bool italic)
{

}

void BasicCharacter::SetSize(int size)
{

}



}  // le

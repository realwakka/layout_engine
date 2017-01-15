#include "character.h"

#include "model/run.h"
#include "model/word.h"

#include "model/character/space_character.h"
#include "model/face/face_manager.h"
#include "model/character/space_character.h"
#include "model/character/basic_character.h"

#include <iostream>

namespace le {

Character* CreateCharacter(char ch)
{
  switch(ch) {
    case ' ':
      return new SpaceCharacter();
    default:
      return new BasicCharacter(ch);
  }
}


Character::Character(char c)
    : c_(c)
{}

Character::~Character()
{}

Character* Character::GetPrevWordCharacter()
{
  if( word_node_.GetContainer()->GetFirstCharacter() == this )
    return nullptr;
  else 
    return *word_node_.GetPrev();
}
Character* Character::GetNextWordCharacter()
{
  if( word_node_.GetContainer()->GetLastCharacter() == this )
    return nullptr;
  else 
    return *word_node_.GetNext();
}



Character* Character::GetPrevRunCharacter()
{
  if( run_node_.GetContainer()->GetFirstCharacter() == this )
    return nullptr;
  else 
    return *run_node_.GetPrev();
}
Character* Character::GetNextRunCharacter()
{
  if( run_node_.GetContainer()->GetLastCharacter() == this )
    return nullptr;
  else 
    return *run_node_.GetNext();
}

void Character::UpdateGlyph()
{
  glyph_ = FaceManager::GetInstance()->GetGlyph(GetRun()->GetRunProp(), *this);
}


}  // le

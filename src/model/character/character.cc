#include "character.h"

#include "model/run.h"
#include "model/word.h"

#include "model/character/space_character.h"
#include "model/face/face_manager.h"

#include <iostream>

namespace le {

Character::Character(char c)
    : c_(c)
{}

Character::~Character()
{}

void Character::InsertChar(Character* character)
{
  auto prev_char = GetPrevWordCharacter();
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

void Character::SetBold(bool bold)
{

}

void Character::SetItalic(bool italic)
{

}

void Character::SetSize(int size)
{

}



}  // le

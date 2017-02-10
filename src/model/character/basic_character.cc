#include "basic_character.h"

#include "model/run.h"
#include "model/paragraph.h"

namespace le {

BasicCharacter::BasicCharacter(char c)
    : Character(c),
      view_(*this)
{}

BasicCharacter::~BasicCharacter()
{}


Character* BasicCharacter::GetNextCharacter()
{
  auto next_runchar = GetNextRunCharacter();
  if( next_runchar ) {
    return next_runchar;
  } else {
    auto next_run = GetRun()->GetNextRun();
    if( next_run ) {
      return next_run->GetFirstCharacter();
    } else {
      return GetRun()->GetParagraph()->GetEnterChar();
    }
  }
}

Character* BasicCharacter::GetPrevCharacter()
{
  auto prev_runchar = GetPrevRunCharacter();
  if( prev_runchar ) {
    return prev_runchar;
  } else {
    auto prev_run = GetRun()->GetPrevRun();
    if( prev_run ) {
      return prev_run->GetFirstCharacter();
    } else {
      return GetRun()->GetParagraph()->GetEnterChar();
    }
  }
}



}  // le

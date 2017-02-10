#include "space_character.h"

#include "model/word.h"
#include "model/run.h"
#include "model/paragraph.h"

namespace le {

SpaceCharacter::SpaceCharacter()
    : Character(' '),
      view_(*this)
{}

SpaceCharacter::~SpaceCharacter()
{}

Character* SpaceCharacter::GetNextCharacter()
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

Character* SpaceCharacter::GetPrevCharacter()
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

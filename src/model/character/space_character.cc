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
  auto next_para_char = GetNextParagraphCharacter();
  if( next_para_char ) {
    return next_para_char;
  } else {
    auto next_paragraph = GetRun()->GetParagraph()->GetNextSibling();
    if( next_paragraph ) {
      return next_paragraph->GetFirstCharacter();
    } else {
      return nullptr;
    }
  }
}

Character* SpaceCharacter::GetPrevCharacter()
{
  auto prev_paragraph_char = GetPrevParagraphCharacter();
  if( prev_paragraph_char ) {
    return prev_paragraph_char;
  } else {
    auto prev_paragraph = GetRun()->GetParagraph()->GetPrevSibling();
    if( prev_paragraph ) {
      return prev_paragraph->GetLastCharacter();
    } else {
      return nullptr;
    }
  }
}

Character* SpaceCharacter::GetNextParagraphCharacter()
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

Character* SpaceCharacter::GetPrevParagraphCharacter()
{
  auto prev_runchar = GetPrevRunCharacter();
  if( prev_runchar ) {
    return prev_runchar;
  } else {
    auto prev_run = GetRun()->GetPrevRun();
    if( prev_run ) {
      return prev_run->GetLastCharacter();
    } else {
      return nullptr;
    }
  }
}




}  // le

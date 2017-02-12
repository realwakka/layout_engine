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

Character* BasicCharacter::GetPrevCharacter()
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

Character* BasicCharacter::GetNextParagraphCharacter()
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

Character* BasicCharacter::GetPrevParagraphCharacter()
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

Character* BasicCharacter::RemoveThis()
{
  // auto prev = GetPrevRunCharacter();
  // GetRun()->RemoveCharacter(this);
  // if( !GetRun()->GetFirstCharacter() ) {
  //   GetRun()->RemoveThis();
  // }
  
  
  // auto prev = GetPrevCharacter();
  // if( GetRun()->GetFirstCharacter() == GetRun()->GetLastCharacter() ) {
  //   GetRun()->GetParagraph()->RemoveRun(GetRun());
  // } else {
  //   GetRun()->RemoveCharacter(this);
  // }
  // return prev;
}

void BasicCharacter::InsertThis(Character* selected)
{
  // if( GetRun() ) {
    
  // } else {
  //   selected->GetPrevCharacter();
  // }
}


}  // le

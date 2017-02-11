#include "enter_character.h"

#include "model/word.h"
#include "space_character.h"
#include "basic_character.h"
#include "model/text_run.h"
#include "model/paragraph.h"
#include "controller/enter_char_controller.h"
#include <typeinfo>

namespace le {

EnterCharacter::EnterCharacter(EnterRun* enter_run_)
    : Character('\n'),
      view_(*this)
{
  SetRun(enter_run_);
}

EnterCharacter::~EnterCharacter()
{}

// std::unique_ptr<Controller> EnterCharacter::GetController(RenderText* rendertext)
// {
//   return std::unique_ptr<EnterCharController>(new EnterCharController(*this, rendertext));
// }

Character* EnterCharacter::GetNextCharacter()
{
  auto next_paragraph = GetRun()->GetParagraph()->GetNextSibling();
  if( next_paragraph ) {
    auto first_run = next_paragraph->GetFirstRun();
    if( first_run ) {
      return first_run->GetFirstCharacter();
    } else {
      return next_paragraph->GetEnterChar();
    }
  } else {
    return nullptr;
  }
}

Character* EnterCharacter::GetPrevCharacter()
{
  auto last_run = GetRun()->GetParagraph()->GetFirstRun();
  if( last_run ) {
    return last_run->GetLastCharacter();
  } else {
    auto prev_paragraph = GetRun()->GetParagraph()->GetPrevSibling();
    if( prev_paragraph ) {
      return prev_paragraph->GetEnterChar();
    } else {
      return nullptr;
    }
  }
}



}  // le

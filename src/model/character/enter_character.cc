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

std::unique_ptr<Controller> EnterCharacter::GetController()
{
  return std::unique_ptr<EnterCharController>(new EnterCharController(*this));
}


}  // le

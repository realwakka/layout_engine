#include "caret_selection.h"

#include "model/character/enter_character.h"
#include "model/character/character.h"
#include "controller/enter_char_controller.h"
#include <memory>

namespace le {


CaretSelection::CaretSelection(Character& character)
    : character_(character),
      view_(*this)
{
  
}

CaretSelection::~CaretSelection()
{}

std::unique_ptr<Controller> CaretSelection::GetController() const
{
  return character_.GetController();
}

View& CaretSelection::GetView() 
{
  return view_;
}


}  // le

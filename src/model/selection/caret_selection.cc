#include "caret_selection.h"

#include "model/character/enter_character.h"
#include "model/character/character.h"
#include "controller/caret_controller.h"
#include <memory>

namespace le {

CaretSelection::CaretSelection(Character& character)
    : character_(character),
      view_(*this),
      x_(character.GetView().GetAbsolutePosition().GetX())

{

}

CaretSelection::CaretSelection(Character& character, int x)
    : character_(character),
      view_(*this),
      x_(x)
{
  
}

CaretSelection::~CaretSelection()
{}

View& CaretSelection::GetView() 
{
  return view_;
}




}  // le

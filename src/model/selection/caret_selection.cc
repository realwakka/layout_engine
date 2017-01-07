#include "caret_selection.h"

#include "model/character/enter_character.h"
#include "model/character/character.h"
#include "controller/enter_char_controller.h"
#include <memory>

namespace le {


CaretSelection::CaretSelection(Character& character)
    : character_(character)
{
  
}

CaretSelection::~CaretSelection()
{}

std::unique_ptr<Controller> CaretSelection::GetController() const
{
  return character_.GetController();
}

SelectionView& CaretSelection::GetSelectionView() const
{
}


}  // le

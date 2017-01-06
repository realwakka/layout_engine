#include "caret_selection.h"

namespace le {


CaretSelection::CaretSelection(Character& character)
    : character_(character)
{
  
}

CaretSelection::~CaretSelection()
{}

std::unique_ptr<Controller> CaretSelection::GetController() const
{
  
}

SelectionView& CaretSelection::GetSelectionView() const
{
  
}


}  // le

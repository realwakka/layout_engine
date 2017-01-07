#include "caret_selection_view.h"

#include "model/selection/caret_selection.h"
#include "model/character/character.h"

namespace le {

CaretSelectionView::CaretSelectionView(CaretSelection& caret_selection)
    : caret_selection_(caret_selection)
{

}

CaretSelectionView::~CaretSelectionView()
{

}

void CaretSelectionView::Layout()
{
  auto view = caret_selection_.GetCharacter().GetView();
  view.AddChildAt(0, this);
}

void CaretSelectionView::Paint(Canvas& canvas)
{
  auto line = caret_selection_.GetCharacter().GetView().GetParent()->GetParent();
  auto height = line->GetHeight();
  auto width = 5;

  
  
  
}

}  // le

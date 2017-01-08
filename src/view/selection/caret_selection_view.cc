#include "caret_selection_view.h"

#include "model/selection/caret_selection.h"
#include "model/character/character.h"

#include "graphic/point.h"
#include "graphic/canvas.h"

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
  SetX(view.GetX());
  SetY(view.GetY());
}

void CaretSelectionView::Paint(Canvas& canvas)
{
  auto line = caret_selection_.GetCharacter().GetView().GetParent()->GetParent();
  auto height = line->GetHeight();
  auto width = 5;

  Point p1(GetX(), GetY());
  Point p2(GetX() + width, GetY() + height);
  
  canvas.DrawRect(p1, p2, kColorBlack);
  
}

}  // le

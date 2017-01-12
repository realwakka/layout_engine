#include "caret_selection_view.h"

#include "model/selection/caret_selection.h"
#include "model/character/character.h"

#include "graphic/paint.h"
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
  auto pos = caret_selection_.GetCharacter().GetView().GetAbsolutePosition();
  SetX(pos.GetX());
  SetY(pos.GetY());
}

void CaretSelectionView::Paint(Canvas& canvas)
{
  auto line = caret_selection_.GetCharacter().GetView().GetParent();
  auto height = line->GetHeight();
  auto width = 5;

  Point p1(GetX(), GetY());
  Point p2(GetX() + width, GetY() + height);

  // Paint p;
  // paint.SetStyle(Paint::Style::kStroke);
  // canvas.DrawRect(p1, p2, paint);
  
}

}  // le

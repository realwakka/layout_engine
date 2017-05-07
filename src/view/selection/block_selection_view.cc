#include "view/selection/block_selection_view.h"

#include "model/selection/block_selection.h"
#include "model/character/character.h"

#include "graphic/paint.h"
#include "graphic/point.h"
#include "graphic/canvas.h"


namespace le {

BlockSelectionView::BlockSelectionView(BlockSelection& block_selection)
    : block_selection_(block_selection)
{

}
BlockSelectionView::~BlockSelectionView()
{

}

void BlockSelectionView::Layout()
{
  // auto pos = caret_selection_.GetCharacter().GetView().GetAbsolutePosition();
  // SetX(pos.GetX());
  // SetY(pos.GetY());
  
}

void BlockSelectionView::Paint(Canvas& canvas)
{
  auto start = block_selection_.GetStart();
  auto end = block_selection_.GetEnd();

  auto character = start;
  while( character != end ) {
    auto& view = character->GetView();
    auto pos1 = view.GetAbsolutePosition();
    le::Point pos2(pos1.GetX() + view.GetWidth(), pos1.GetY() + view.GetHeight());
               
    le::Paint paint;
    paint.SetStyle(Paint::Style::kFill);
    canvas.DrawRect(pos1, pos2, paint);
    
    character = character->GetNextCharacter();
  }
}


}  // le

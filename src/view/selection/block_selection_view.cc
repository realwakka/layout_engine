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
  auto& startCharView = start->GetView();
  auto& endCharView = start->GetView();

  auto startLineView = startCharView.GetParent()->GetParent();
  auto endLineView = endCharView.GetParent()->GetParent();

  if( startLineView == endLineView ) {
    auto st_pos = startCharView.GetAbsolutePosition();
    auto ed_pos = endCharView.GetAbsolutePosition();
    ed_pos.SetY(ed_pos.GetY() + startLineView->GetHeight());
    le::Paint paint;
    paint.SetStyle(Paint::Style::kStroke);
    canvas.DrawRect(st_pos, ed_pos, paint);

  }
}


}  // le

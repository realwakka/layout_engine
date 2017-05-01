#include "view/selection/block_selection_view.h"

#include "model/selection/block_selection.h"

namespace le {

BlockSelectionView::BlockSelectionView(std::shared_ptr<BlockSelection> block_selection)
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
  auto selection = block_selection_.lock();
  if( selection ) {
    auto start = selection->GetStart();
    auto end = selection->GetEnd();

  }
}


}  // le

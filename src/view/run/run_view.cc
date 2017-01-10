#include "run_view.h"

namespace le {

RunView::RunView(Run& run)
    : run_(run)
{}

RunView::~RunView()
{}

void RunView::Layout()
{
  view_util::SetHorizontalBlockPosition(this);
  for(int i=0 ; i<GetChildCount() ; i++ )
    GetChildAt(i)->Layout();
}

void RunView::Paint(Canvas& canvas)
{
  for(int i=0 ; i<GetChildCount() ; i++ )
    GetChildAt(i)->Paint(canvas);
}

View* RunView::GetNextParent() const
{
  auto nextparent = GetParent()->GetNextParent();
  auto newview = new RunView(GetRun());
  nextparent->AddChildAt(0, newview);
  return newview;
}


}  // le

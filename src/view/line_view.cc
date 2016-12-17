#include "line_view.h"

#include "view/word_view.h"

namespace le {

LineView::LineView()
{

}
LineView::~LineView()
{}

void LineView::Paint(Canvas& canvas)
{
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Paint(canvas);
}
    

}  // le

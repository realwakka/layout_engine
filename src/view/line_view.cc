#include "line_view.h"

#include "view/word_view.h"
#include "graphic/canvas.h"

namespace le {

LineView::LineView()
{

}
LineView::~LineView()
{}

void LineView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());
  
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Paint(canvas);

  canvas.Restore();
}

void LineView::Layout()
{
  SetX(0);

  auto line_index = 0;
  for( ; line_index < GetChildCount() ; ++line_index )
    if( GetChildAt(line_index) == this )
      break;
  
  if( line_index == 0 ) {
    SetY(0);
  }
  else {
    auto prev = GetChildAt(line_index - 1);
    SetY(prev->GetY() + prev->GetHeight());
  }

  auto maxheight = 0;
  for( auto index = 0; index < GetChildCount() ; ++index ) {
    auto child = GetChildAt(index);
    child->Layout();
    maxheight = std::max( maxheight, child->GetHeight() );
  }

  SetHeight(maxheight);
}
    

}  // le

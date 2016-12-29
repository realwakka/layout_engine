#include "line_view.h"

#include "view/word_view.h"
#include "graphic/canvas.h"

#include "model/word.h"

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
  SetWidth(GetParent()->GetWidth());

  auto line_index = GetIndex();
  if( line_index == 0 ) {
    SetY(0);
  }
  else {
    auto prev = GetParent()->GetChildAt(line_index - 1);
    SetY(prev->GetY() + prev->GetHeight());
  }

  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Layout();
  
  auto maxheight = 0;
  auto baseline = 0;

  for( auto index = 0; index < GetChildCount() ; ++index ) {
    auto child = static_cast<WordView*>(GetChildAt(index));
    maxheight = std::max( maxheight, child->GetHeight() );
    baseline = std::max(baseline, child->GetWord().GetWordAscender());
  }

  SetHeight(maxheight);
  SetBaseline(baseline);
}

View* LineView::GetNextParent() const
{
  auto nextline = GetNextSibling();
  if( !nextline ) {
    nextline = new LineView();
    GetParent()->AddChildAt(GetParent()->GetChildCount(), nextline);
  }

  return nextline;
}
    

}  // le

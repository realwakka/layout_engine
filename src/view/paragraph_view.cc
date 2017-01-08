#include "paragraph_view.h"

#include "view/line_view.h"
#include "model/paragraph.h"

namespace le {

ParagraphView::ParagraphView(Paragraph& paragraph)
    : paragraph_(paragraph)
{
  auto firstline = new LineView();
  AddChildAt(0, firstline);
  auto& enterview = paragraph.GetEnterRun()->GetEnterChar()->GetView();
  firstline->AddChildAt(0,&enterview);
}
ParagraphView::~ParagraphView()
{
}


void ParagraphView::Paint(Canvas& canvas)
{
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Paint(canvas);
}

void ParagraphView::Layout()
{
  SetX(0);
  SetY(0);
  
  if( GetParent() ) {
    SetWidth(GetParent()->GetWidth());
  } else {
    SetWidth(500);
  }
  
  //SetHeight(999999);
  
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Layout();

  auto last = GetChildAt(GetChildCount() - 1);
  SetHeight(last->GetHeight() + last->GetY());
}

}  // le

#include "paragraph_view.h"

#include "view/line_view.h"

namespace le {

ParagraphView::ParagraphView(Paragraph& paragraph)
    : paragraph_(paragraph)
{
  AddChildAt(0, new LineView());
}
ParagraphView::~ParagraphView()
{
}


void ParagraphView::Paint(Canvas& canvas)
{
  
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Paint(canvas);
}

}  // le

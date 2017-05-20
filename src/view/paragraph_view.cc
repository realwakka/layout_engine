#include "paragraph_view.h"

#include "view/line_view.h"
#include "view/page/page_view.h"
#include "model/paragraph.h"
#include "view/linebreaker/word_linebreaker.h"

#include "graphic/canvas.h"

namespace le {

ParagraphView::ParagraphView(Paragraph& paragraph)
    : paragraph_(paragraph)
{
  auto firstline = new LineView();
  AddChildAt(0, firstline);
  auto& enterview = paragraph.GetEnterRun()->GetEnterChar()->GetView();
  firstline->AddChildAt(0,const_cast<CharacterView*>(&enterview));
}
ParagraphView::~ParagraphView()
{
}


void ParagraphView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());
  
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Paint(canvas);

  canvas.Restore();
}

void ParagraphView::Layout()
{
  auto page = static_cast<PageView*>(GetParent());
  SetX(page->GetLeftMargin());
  SetY(page->GetTopMargin());

  SetWidth( page->GetWidth() - page->GetLeftMargin() - page->GetRightMargin() );

  GetParagraph().GetProp().GetLineBreaker()->BreakLine(GetParagraph());
  
  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Layout();

  auto last = GetChildAt(GetChildCount() - 1);
  SetHeight(last->GetHeight() + last->GetY());
}

}  // le

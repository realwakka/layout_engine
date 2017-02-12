#include "document.h"

#include "model/paragraph.h"

namespace le {

Document::Document(RenderText* rendertext)
    : view_(*this),
      rendertext_(rendertext)
{
  //AppendChild(new Paragraph());
  AddChildAt(0, new Paragraph());
  view_.createPageViews();
}

Document::~Document()
{}

}  // le

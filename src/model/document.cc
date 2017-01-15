#include "document.h"

#include "model/paragraph.h"

namespace le {

Document::Document()
    : view_(*this)
{
  //AppendChild(new Paragraph());
  AddChildAt(0, new Paragraph());

  view_.createPageViews();
}

Document::~Document()
{}

}  // le

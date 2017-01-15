#include "document.h"

#include "model/paragraph.h"

namespace le {

Document::Document()
    : view_(*this)
{
  //AppendChild(new Paragraph());
  AddChildAt(0, new Paragraph());
}

Document::~Document()
{}

}  // le

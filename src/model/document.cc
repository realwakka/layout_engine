#include "document.h"

#include "model/paragraph.h"

namespace le {

Document::Document()
{
  block_list_.push_back(new Paragraph());
}

Document::~Document()
{}

}  // le

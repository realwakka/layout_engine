#include "enter_run.h"

#include "paragraph.h"
#include "text_run.h"

namespace le {

EnterRun::EnterRun(Paragraph* paragraph)
    : enter_char_(this)
{
  SetParagraph(paragraph);
  InsertCharacter(&enter_char_, nullptr);
}

EnterRun::~EnterRun()
{}

// Run* EnterRun::Clone()
// {
//   return new EnterRun(*this);
// }


}  // le

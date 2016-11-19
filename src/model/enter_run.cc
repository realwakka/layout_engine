#include "enter_run.h"

#include "paragraph.h"
#include "text_run.h"

namespace le {

EnterRun::EnterRun()
    : enter_char_('\n')
{}

EnterRun::~EnterRun()
{}

void EnterRun::InsertBefore(Character* character, Character* reference)
{
  auto runs = GetParagraph()->GetRuns();
  if( runs.empty() ) {
    auto text_run = new TextRun(character);
    GetParagraph()->InsertBefore(text_run, nullptr);
    
  }
  else {

  }
}


}  // le

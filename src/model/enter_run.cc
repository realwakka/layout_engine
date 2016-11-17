#include "enter_run.h"

#include "paragraph.h"

namespace le {

EnterRun::EnterRun()
    : enter_char_('\n')
{}

EnterRun::~EnterRun()
{}

void EnterRun::insertRun(Run* run)
{
  getParagraph()->insertBefore(run, this);
}

}  // le

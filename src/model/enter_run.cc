#include "enter_run.h"

namespace le {

EnterRun::EnterRun()
{}

EnterRun::~EnterRun()
{}

void EnterRun::insertRun(Run* run)
{
  getParagraph()->insertBefore(run, this);
}

}  // le

#include "run.h"

#include "model/face/face.h"
#include "model/paragraph.h"

namespace le {

Run::Run()
{

}

Run::~Run()
{
  
}


Run* Run::GetPrevRun()
{
  if( node_.GetContainer()->GetFirstRun() == this )
    return nullptr;
  else
    return *node_.GetPrev();
}

Run* Run::GetNextRun()
{
  if( node_.GetContainer()->GetLastRun() == this )
    return nullptr;
  else
    return *node_.GetNext();
}



}  // le

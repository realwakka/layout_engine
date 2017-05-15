#include "event.h"

namespace le {

Event::Event()
    : flags_(0)
{}

Event::~Event()
{}

void Event::SetFlag(EventFlags flag, bool value)
{
  if( value ) {
    flags_ |= flag;
  } else {
    flags_ |= flag;
    flags_ -= flag;
  }
  
}


}  // le

#include "event.h"

namespace le {

Event::Event()
    : shift_down_(false),
      ctrl_down_(false),
      alt_down_(false),
      command_down_(false)
{}

Event::~Event()
{}


}  // le

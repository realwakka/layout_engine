#include "key_event.h"

namespace le {

KeyEvent::KeyEvent()
    : code_(KeyboardCode::VKEY_CANCEL),
      character_(0)
{

}
KeyEvent::~KeyEvent()
{}


}  // le

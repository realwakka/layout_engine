#ifndef LE_KEY_EVENT_H_
#define LE_KEY_EVENT_H_

#include "controller/event/keyboard_codes.h"

namespace le {

class KeyEvent
{
 public:
  KeyEvent();
  virtual ~KeyEvent();

  KeyboardCode GetCode() const { return code_; }
  void SetCode(KeyboardCode code) { code_ = code; }
  
  char GetChar() const { return character_; }
  void SetChar(char character) { character_ = character; }
  
 private:
  KeyboardCode code_;
  char character_;
};

}  // le


#endif /* LE_KEY_EVENT_H_ */

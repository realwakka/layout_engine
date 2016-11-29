#ifndef LE_ENTER_RUN_H_
#define LE_ENTER_RUN_H_

#include "run.h"
#include "model/character/enter_character.h"

namespace le {

class EnterRun : public Run
{
 public:
  EnterRun();
  virtual ~EnterRun();

  EnterCharacter* GetEnterChar() { return &enter_char_; }

 private:
  EnterCharacter enter_char_;
};

}  // le

#endif /* LE_ENTER_RUN_H_ */


#ifndef LE_ENTER_RUN_H_
#define LE_ENTER_RUN_H_

#include "run.h"
#include "model/character/character.h"

namespace le {

class EnterRun : public Run
{
 public:
  EnterRun();
  virtual ~EnterRun();

  Character* getEnterChar() { return &enter_char_; }
  virtual void InsertBefore(Character* character, Character* reference) override;

 private:
  Character enter_char_;
};

}  // le

#endif /* LE_ENTER_RUN_H_ */


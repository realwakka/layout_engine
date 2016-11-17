#ifndef LE_ENTER_RUN_H_
#define LE_ENTER_RUN_H_

#include "run.h"
#include "character.h"

namespace le {

class EnterRun : public Run
{
 public:
  EnterRun();
  virtual ~EnterRun();

  virtual void insertRun(Run* run) override;

  Character* getEnterChar() { return &enter_char_; }

 private:
  Character enter_char_;
};

}  // le

#endif /* LE_ENTER_RUN_H_ */


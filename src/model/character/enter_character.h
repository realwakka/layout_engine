#ifndef LE_ENTER_CHARACTER_H_
#define LE_ENTER_CHARACTER_H_

#include "character.h"

namespace le {

class EnterRun;
class Run;

class EnterCharacter : public Character
{
 public:
  EnterCharacter(EnterRun* enter_run_);
  virtual ~EnterCharacter();

  virtual void InsertChar(Character* character) override;
  virtual void SetBold(bool bold) override;
  
 private:
  Run* cache_run_;
};


}  // le

#endif /* LE_ENTER_CHARACTER_H_ */

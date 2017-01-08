#ifndef LE_ENTER_CHARACTER_H_
#define LE_ENTER_CHARACTER_H_

#include "character.h"
#include "view/character/enter_character_view.h"

namespace le {

class EnterRun;
class Run;

class EnterCharacter : public Character
{
 public:
  EnterCharacter(EnterRun* enter_run_);
  virtual ~EnterCharacter();

  virtual CharacterView& GetView() override { return view_; }
  virtual std::unique_ptr<Controller> GetController() override;
  
 private:
  Run* cache_run_;
  EnterCharacterView view_;
};


}  // le

#endif /* LE_ENTER_CHARACTER_H_ */

#ifndef LE_SPACE_CHARACTER_H_
#define LE_SPACE_CHARACTER_H_

#include "model/character/character.h"
#include "view/space_character_view.h"

namespace le {

class SpaceCharacter : public Character
{
 public:
  SpaceCharacter();
  virtual ~SpaceCharacter();

  virtual void InsertChar(Character* character) override;

  virtual CharacterView& GetView() override { return view_; }

 private:
  SpaceCharacterView view_;
};


}  // le

#endif /* LE_SPACE_CHARACTER_H_ */

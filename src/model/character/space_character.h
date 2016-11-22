#ifndef LE_SPACE_CHARACTER_H_
#define LE_SPACE_CHARACTER_H_

#include "model/character/character.h"

namespace le {

class SpaceCharacter : public Character
{
 public:
  SpaceCharacter();
  virtual ~SpaceCharacter();

  virtual void InsertChar(Character* character) override;
};


}  // le

#endif /* LE_SPACE_CHARACTER_H_ */

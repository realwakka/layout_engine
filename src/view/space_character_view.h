#ifndef LE_SPACE_CHARACTER_VIEW_H_
#define LE_SPACE_CHARACTER_VIEW_H_

#include "view/character_view.h"

namespace le {

class SpaceCharacter;

class SpaceCharacterView : public CharacterView
{
 public:
  SpaceCharacterView(SpaceCharacter& space_character);
  virtual ~SpaceCharacterView();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;

};


}  // le

#endif /* LE_SPACE_CHARACTER_VIEW_H_ */

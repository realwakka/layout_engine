#ifndef LE_ENTER_CHARACTER_VIEW_H_
#define LE_ENTER_CHARACTER_VIEW_H_

#include "view/character/character_view.h"

namespace le {

class EnterCharacter;

class EnterCharacterView : public CharacterView
{
 public:
  EnterCharacterView(EnterCharacter& enter_character);
  virtual ~EnterCharacterView();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;

  // bool HitTest(HitItem& hititem, const Point& point) override;
  
};

}  // le

#endif /* LE_ENTER_CHARACTER_VIEW_H_ */

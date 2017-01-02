#ifndef LE_CHARACTER_VIEW_H_
#define LE_CHARACTER_VIEW_H_

#include "view/view.h"

namespace le {

class Character;

class CharacterView : public View
{
 public:
  CharacterView(Character& character);
  virtual ~CharacterView();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;

  Character& GetCharacter() const { return character_; }

  virtual int GetCharacterWidth() const;
  virtual int GetSpaceWidth() const;

 private:
  Character& character_;
};


}  // le

#endif /* LE_CHARACTER_VIEW_H_ */

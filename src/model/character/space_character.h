#ifndef LE_SPACE_CHARACTER_H_
#define LE_SPACE_CHARACTER_H_

#include "model/character/character.h"
#include "view/character/space_character_view.h"
#include "model/run.h"

namespace le {

class SpaceCharacter : public Character
{
 public:
  SpaceCharacter();
  virtual ~SpaceCharacter();

  virtual CharacterView& GetView() override { return view_; }
  
  Character* GetNextCharacter() override;
  Character* GetPrevCharacter() override;

  Character* GetNextParagraphCharacter() override;
  Character* GetPrevParagraphCharacter() override;

  Paragraph* GetParagraph() override { return GetRun()->GetParagraph(); }

  Character* RemoveThis() override;
  void InsertThis(Character* selected) override;

 private:
  SpaceCharacterView view_;
};


}  // le

#endif /* LE_SPACE_CHARACTER_H_ */

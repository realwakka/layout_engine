#ifndef LE_ENTER_CHARACTER_H_
#define LE_ENTER_CHARACTER_H_

#include "character.h"
#include "view/character/enter_character_view.h"
#include "model/run.h"

namespace le {

class EnterRun;
class Run;
class RenderText;

class EnterCharacter : public Character
{
 public:
  EnterCharacter(EnterRun* enter_run_);
  virtual ~EnterCharacter();

  CharacterView& GetView() override { return view_; }

  Character* GetNextCharacter() override;
  Character* GetPrevCharacter() override;

  Character* GetNextParagraphCharacter() override;
  Character* GetPrevParagraphCharacter() override;

  Paragraph* GetParagraph() override { return GetRun()->GetParagraph(); }

  Character* RemoveThis() override;
  void InsertThis(Character* selected) override;
  
 private:
  EnterCharacterView view_;
};


}  // le

#endif /* LE_ENTER_CHARACTER_H_ */

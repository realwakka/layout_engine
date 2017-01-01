#ifndef LE_BASIC_CHARACTER_H_
#define LE_BASIC_CHARACTER_H_

#include "model/character/character.h"

namespace le {

class BasicCharacter : public Character
{
 public:
  BasicCharacter(char c);
  virtual ~BasicCharacter();
  
  virtual CharacterView& GetView() override { return view_; }

  virtual void InsertChar(Character* character) override;
  virtual void SetBold(bool bold) override;
  virtual void SetItalic(bool italic) override;
  virtual void SetSize(int size) override;
  

 private:
  CharacterView view_;
  
};


}  // le


#endif /* LE_BASIC_CHARACTER_H_ */


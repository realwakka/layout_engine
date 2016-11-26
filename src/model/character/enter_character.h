#ifndef LE_ENTER_CHARACTER_H_
#define LE_ENTER_CHARACTER_H_

namespace le {

class EnterCharacter
{
 public:
  EnterCharacter();
  virtual ~EnterCharacter();

  virtual void InsertChar(Character* character) override;
};


}  // le

#endif /* LE_ENTER_CHARACTER_H_ */

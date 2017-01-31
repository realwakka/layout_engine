#ifndef LE_CHAR_COMMAND_DELEGATE_H_
#define LE_CHAR_COMMAND_DELEGATE_H_

namespace le {

class Character;
class Paragraph;

class CharCommandDelegate
{
 public:
  virtual void Apply(Character* character, Paragraph* paragraph) = 0;
  virtual void UnApply(Character* character, Paragraph* paragraph) = 0;
  virtual void ReApply(Character* character, Paragraph* paragraph) = 0;
};


}  // le

#endif /* LE_CHAR_COMMAND_DELEGATE_H_ */

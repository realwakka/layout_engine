#ifndef LE_DEL_CHAR_DELEGATE_H_
#define LE_DEL_CHAR_DELEGATE_H_

#include "controller/command/char_command_delegate.h"

namespace le {

class TextRun;

class DelCharDelegate : public CharCommandDelegate
{
 public:
  DelCharDelegate();
  virtual ~DelCharDelegate();
  
  void Apply(Character* character, Paragraph* paragraph) override;
  void UnApply(Character* character, Paragraph* paragraph) override;
  
 private:
  TextRun* run_;
  Character* char_;
};


}  // le

#endif /* LE_DEL_CHAR_DELEGATE_H_ */

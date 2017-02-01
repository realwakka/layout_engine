#ifndef LE_INSERT_CHAR_COMMAND_H_
#define LE_INSERT_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Paragraph;
class Character;
class CharCommandDelegate;

class InsertCharCommand : public Command
{
 public:
  InsertCharCommand(Paragraph* paragraph, Character* character, Character* inserted);

  virtual ~InsertCharCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;
  std::string GetDecription() override { return "Insert Char"; }

 private:
  //selected
  Paragraph* paragraph_;
  Character* character_;
  Character* inserted_;

};


}  // le


#endif /* LE_INSERT_CHAR_COMMAND_H_ */

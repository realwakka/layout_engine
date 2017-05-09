#ifndef LE_INSERT_CHAR_COMMAND_H_
#define LE_INSERT_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Paragraph;
class Character;
class Run;

class InsertCharCommand : public Command
{
 public:
  InsertCharCommand(Character* inserted, Character* selected);
  virtual ~InsertCharCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;
  std::string GetDecription() override { return "Insert Char"; }

 private:
  //selected
  Character* selected_;
  Character* inserted_;
  Run* inserted_run_;
  Paragraph* inserted_para_;

};


}  // le


#endif /* LE_INSERT_CHAR_COMMAND_H_ */

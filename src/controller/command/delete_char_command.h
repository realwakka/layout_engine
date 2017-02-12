#ifndef LE_DELETE_CHAR_COMMAND_H_
#define LE_DELETE_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Paragraph;
class Character;

class DeleteCharCommand : public Command
{
 public:
  DeleteCharCommand(Character* selected);
  virtual ~DeleteCharCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { "Modify Char"; }

 private:
  Character* selected_;
  Character* deleted_;

  
};


}  // le

#endif /* LE_DELETE_CHAR_COMMAND_H_ */

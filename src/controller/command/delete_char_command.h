#ifndef LE_DELETE_CHAR_COMMAND_H_
#define LE_DELETE_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Paragraph;
class Character;

class DeleteCharCommand : public Command
{
 public:
  DeleteCharCommand(Paragraph* paragraph, Character* character);
  virtual ~DeleteCharCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { "Modify Char"; }

 private:
  Paragraph* paragraph_;
  Character* character_;
  Character* inserted_;

  
};


}  // le

#endif /* LE_DELETE_CHAR_COMMAND_H_ */

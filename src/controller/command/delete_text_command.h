#ifndef LE_DELETE_TEXT_COMMAND_H_
#define LE_DELETE_TEXT_COMMAND_H_

#include <memory>
#include "controller/command/delete_char_command.h"
#include "controller/command/command.h"

namespace le {

class Character;

class DeleteTextCommand : public Command
{
 public:
  DeleteTextCommand(Character* begin, Character* end);
  virtual ~DeleteTextCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "DeleteTextCommand"; }

 private:
  std::vector<std::unique_ptr<DeleteCharCommand>> char_command_list_;
  Character* begin_;
  Character* end_;
  
};


}  // le

#endif /* LE_DELETE_TEXT_COMMAND_H_ */

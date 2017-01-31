#ifndef LE_COMMAND_STACK_H_
#define LE_COMMAND_STACK_H_

#include "controller/command/command.h"

namespace le {

class CommandStack
{
 public:
  CommandStack();
  virtual ~CommandStack();

  template<typename CommandType, typename... Args>
  void DoCommand(Args&&... args);

  void DoCommand(Command* command);
  void UndoCommand();
  void RedoCommand();

  static CommandStack* GetInstance();

 private:
  Command* current_;
  static CommandStack* instance_;
};

template<typename CommandType, typename... Args>
void CommandStack::DoCommand(Args&&... args)
{
  auto command = new CommandType(args...);
  command->Apply();
  current_->AppendChild(command);
  current_ = command;
}



}  // le

#endif /* LE_COMMAND_STACK_H_ */

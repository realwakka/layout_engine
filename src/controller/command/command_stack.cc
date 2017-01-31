#include "command_stack.h"

#include "controller/command/initial_command.h"

namespace le {

CommandStack* CommandStack::instance_ = nullptr;

CommandStack* CommandStack::GetInstance()
{
  if( instance_ == nullptr )
    instance_ = new CommandStack();
  return instance_;
}

CommandStack::CommandStack()
    : current_(new InitialCommand)
{}
CommandStack::~CommandStack()
{}

void CommandStack::DoCommand(Command* command)
{
  command->Apply();
  current_->AppendChild(command);
  current_ = command;
}

void CommandStack::UndoCommand()
{
  current_->UnApply();
  
  auto parent = current_->GetParent();
  if( parent ) {
    current_ = parent;
  }
}

void CommandStack::RedoCommand()
{
  auto child = current_->GetLastChild();
  if( child ) {
    current_ = child;
    current_->ReApply();
  }
}

}  // le

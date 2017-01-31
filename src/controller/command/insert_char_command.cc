#include "insert_char_command.h"

#include "controller/command/char_command_delegate.h"
#include "controller/command/ins_char_delegate.h"

namespace le {

InsertCharCommand::InsertCharCommand(Paragraph* paragraph, Character* character, Character* inserted)
    : paragraph_(paragraph),
      character_(character)
{
  delegate_list_.push_back(new InsCharDelegate(inserted));
}
InsertCharCommand::~InsertCharCommand()
{}

void InsertCharCommand::Apply() 
{
  for( CharCommandDelegate* delegate : delegate_list_ ) {
    delegate->Apply(character_, paragraph_);
  }
}

void InsertCharCommand::UnApply() 
{
  for( CharCommandDelegate* delegate : delegate_list_ ) {
    delegate->UnApply(character_, paragraph_);
  }
}

void InsertCharCommand::ReApply() 
{
  for( CharCommandDelegate* delegate : delegate_list_ ) {
    delegate->Apply(character_, paragraph_);
  }
}


void InsertCharCommand::AppendChild(Command* child)
{
  if( MergeAvailable(child) ) {
    auto command = static_cast<InsertCharCommand*>(child);
    auto delegate = command->delegate_list_.front();
    if( delegate ) {
      delegate_list_.push_back(delegate);
    } else {
      throw std::exception();
    }
  }
}

bool InsertCharCommand::MergeAvailable(Command* child) const
{
  if( typeid(*child) == typeid(*this) ) {
    auto command = static_cast<InsertCharCommand*>(child);
    if( command->paragraph_ == paragraph_ &&
        command->character_ == character_ ) {
      return true;
    }
  }
  return false;
}

}  // le

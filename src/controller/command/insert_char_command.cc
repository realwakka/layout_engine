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
  
}

}  // le

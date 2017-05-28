#include "controller/command/delete_text_command.h"

#include "model/character/character.h"

namespace le {

DeleteTextCommand::DeleteTextCommand(Character* begin, Character* end)
    : begin_(begin),
      end_(end)
{
}
DeleteTextCommand::~DeleteTextCommand()
{
  
}

void DeleteTextCommand::Apply()
{
  for( auto c = end_ ; c != begin_ ; c = c->GetPrevCharacter() ) {
    auto cmd = new DeleteCharCommand(end_);
    char_command_list_.emplace_back(cmd);
  }
  
  for( auto&& cmd : char_command_list_ )
    cmd->Apply();
    
}
void DeleteTextCommand::UnApply()
{
  for( auto&& cmd : char_command_list_ ) {
    cmd->UnApply();
  }
}
void DeleteTextCommand::ReApply()
{
  for( auto&& cmd : char_command_list_ ) {
    cmd->ReApply();
  }

}


}  // le

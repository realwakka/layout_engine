#include "controller/command/split_run_command.h"

#include "model/character/character.h"
#include "model/run.h"

namespace le {

SplitRunCommand::SplitRunCommand(Character* character)
    : character_(character),
      inserted_run_(nullptr)
{

}
SplitRunCommand::~SplitRunCommand()
{
}

void SplitRunCommand::Apply()
{
  inserted_run_ = character_->GetRun()->Split(character_);
}

void SplitRunCommand::UnApply()
{
  if( inserted_run_ )
    character_->GetRun()->Merge();
}

void SplitRunCommand::ReApply()
{
  Apply();
}


}  // le

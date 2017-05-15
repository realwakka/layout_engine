#include "controller/command/split_run_command.h"

#include "model/paragraph.h"
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
  if( inserted_run_ ) {
    character_->GetRun()->Merge();
    character_->GetRun()->UpdateGlyph();
  }
}

void SplitRunCommand::ReApply()
{
  if( inserted_run_ ) {
    auto ref_run = character_->GetRun();
    std::vector<Character*> removed;
    for( Character* ch = ref_run->GetFirstCharacter() ;
         ch != character_ ; ch = ch->GetNextRunCharacter() ) {
      removed.push_back(ch);
    }

    for( Character* ch : removed ) {
      ref_run->RemoveCharacter(ch);
      inserted_run_->InsertCharacter(ch, nullptr);
    }

    ref_run->GetParagraph()->InsertRun(inserted_run_, ref_run);
  }

}


}  // le

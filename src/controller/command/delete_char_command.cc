#include "controller/command/delete_char_command.h"

#include <typeinfo>
#include <iostream>

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"


namespace le {
namespace {

void BackSpaceRunInternal(Character* selected, Character* &deleted, Run* &deleted_run)
{
  deleted = selected->GetPrevCharacter();
  if( deleted ) {
    deleted_run = deleted->GetRun();
    if( typeid(*deleted) == typeid(BasicCharacter) ||
        typeid(*deleted) == typeid(SpaceCharacter) ) {

      deleted_run->RemoveCharacter(deleted);
      if( deleted_run->GetFirstCharacter() == nullptr ) {
        deleted_run->GetParagraph()->RemoveRun(deleted_run);
      } // else {
      //   deleted_run = 
      //   deleted_run = nullptr;
      // }
    }
  }
}

}

DeleteCharCommand::DeleteCharCommand(Character* selected)
    : selected_(selected),
      deleted_(nullptr),
      deleted_run_(nullptr),
      ref_run_(nullptr),
      deleted_para_(nullptr)
{}

DeleteCharCommand::~DeleteCharCommand()
{}

void DeleteCharCommand::Apply()
{
  BackSpaceRunInternal(selected_, deleted_, deleted_run_);
  selected_->GetParagraph()->CreateWords();
  
  // if( paragraph_ ) {
  //   BackSpaceWordInternal(*paragraph_);
  //   BackSpaceRunInternal(*paragraph_);
  // }
}

void DeleteCharCommand::UnApply()
{
  if( deleted_para_ ) {

  } else if ( deleted_run_ ) {
    if( deleted_run_->GetParagraph() == nullptr) {
      selected_->GetParagraph()->InsertRun(deleted_run_, selected_->GetRun());
      deleted_run_->InsertCharacter(deleted_, nullptr);
    } else {
      if( deleted_run_ == selected_->GetRun() )
        deleted_run_->InsertCharacter(deleted_, selected_);
      else 
        deleted_run_->InsertCharacter(deleted_, nullptr);
    }
  } else {
    
  }
  
  selected_->GetParagraph()->CreateWords();
}

void DeleteCharCommand::ReApply()
{
  BackSpaceRunInternal(selected_, deleted_, deleted_run_);
  selected_->GetParagraph()->CreateWords();
}

}  // le

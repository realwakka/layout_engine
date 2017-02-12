#include "delete_char_command.h"

#include <typeinfo>
#include <iostream>

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"


namespace le {

namespace {

// void InsertWordInternal(Paragraph* paragraph, Character* character)
// {
//   auto last_word = paragraph->GetLastWord();
  
//   if( last_word == nullptr ) {
//     last_word = new Word();
//     paragraph->InsertWord(last_word, nullptr);
//     last_word->InsertCharacter(character, nullptr);
//   } else {
    
//     auto prev_char = last_word->GetLastCharacter();
//     if( typeid(*character) == typeid(BasicCharacter) ) {
//       if( typeid(*prev_char) == typeid(BasicCharacter) ) {
//         last_word->InsertCharacter(character, nullptr);
//       } else if ( typeid(*prev_char) == typeid(SpaceCharacter) ) {
//         last_word->InsertCharacter(character, nullptr);
//         last_word->Split(character);
//       } else {

//       }
//     } else if (typeid(*character) == typeid(SpaceCharacter) ) {
//       if( typeid(*prev_char) == typeid(BasicCharacter) ) {
//         last_word->InsertCharacter(character, nullptr);
//       } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
//         last_word->InsertCharacter(character, nullptr);
//         last_word->Split(character);
//       } else {

//       }
      
//     } else {

//     }
//   }
// }

// void InsertRunInternal(Paragraph* paragraph, Character* character)
// {
//   auto cached = Run::GetCachedRun();
//   if( cached ) {
//     paragraph->InsertRun(cached, nullptr);
//   }
  
//   auto last_run =  paragraph->GetLastRun();

//   if(last_run == nullptr) {
//     last_run = new TextRun();
//     paragraph->InsertRun(last_run, nullptr);
//   }
  
//   last_run->InsertCharacter(character, nullptr);

//   Run::SetCachedRun(nullptr);
// }


// void BackSpaceWordInternal(Paragraph& paragraph)
// {
//   auto last_word = paragraph.GetLastWord();
//   if( last_word == nullptr ) {

//   } else {
//     auto prev_char = last_word->GetLastCharacter();
//     last_word->RemoveCharacter(prev_char);

//     if( last_word->GetFirstCharacter() == nullptr )
//       paragraph.RemoveWord(last_word);
//   }
// }

void BackSpaceRunInternal(Character* selected, Character* &deleted, Run* &deleted_run, Run* &ref_run )
{

  
  deleted = selected->GetPrevCharacter();
  deleted_run = deleted->GetRun();
  if( deleted ) {
    if( typeid(*deleted) == typeid(BasicCharacter) ||
        typeid(*deleted) == typeid(SpaceCharacter) ) {

      auto prev_run = deleted->GetRun();
      prev_run->RemoveCharacter(deleted);
      if( prev_run->GetFirstCharacter() == nullptr ) {
        ref_run = prev_run->GetNextRun();
      } 
    }
  }
}

}

DeleteCharCommand::DeleteCharCommand(Character* selected)
    : selected_(selected),
      deleted_(nullptr),
      deleted_run_(nullptr),
      ref_run_(nullptr)
{}

DeleteCharCommand::~DeleteCharCommand()
{}

void DeleteCharCommand::Apply()
{
  BackSpaceRunInternal(selected_, deleted_, deleted_run_, ref_run_);
  selected_->GetParagraph()->CreateWords();
  
  // if( paragraph_ ) {
  //   BackSpaceWordInternal(*paragraph_);
  //   BackSpaceRunInternal(*paragraph_);
  // }
}

void DeleteCharCommand::UnApply()
{
  auto paragraph = selected_->GetParagraph();
  if( ref_run_ ) {
    paragraph->InsertRun( deleted_run_ , ref_run_ );
    deleted_run_->InsertCharacter(deleted_, nullptr);
  } else {
    if( selected_->GetRun() == deleted_run_ ) {
      deleted_run_->InsertCharacter(deleted_, selected_);
    } else {
      deleted_run_->InsertCharacter(deleted_, nullptr);
    }
  }
  selected_->GetParagraph()->CreateWords();
}

void DeleteCharCommand::ReApply()
{
  BackSpaceRunInternal(selected_, deleted_, deleted_run_, ref_run_);
  selected_->GetParagraph()->CreateWords();
}

}  // le

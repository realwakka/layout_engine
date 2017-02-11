#include "insert_char_command.h"

#include <typeinfo>
#include <iostream>

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"

namespace le {

namespace {

Run* InsertRunInternal(Character* inserted, Character* selected, Run* cached)
{
  Run* inserted_run = nullptr;
  if( cached ) {
    inserted_run = cached;
    if( typeid(*selected) == typeid(EnterCharacter) ) {
      selected->GetRun()->GetParagraph()->InsertRun(cached, nullptr);
      cached->InsertCharacter(inserted, nullptr);
    } else {
      selected->GetRun()->Split(selected);
      selected->GetParagraph()->InsertRun(cached, selected->GetRun());
      cached->InsertCharacter(inserted, nullptr);
    }
    
  } else {
    if( typeid(*selected) == typeid(EnterCharacter) ) {
      auto last_run =  selected->GetRun()->GetParagraph()->GetLastRun();
      if(last_run == nullptr) {
        last_run = new TextRun();
        inserted_run = last_run;
        selected->GetRun()->GetParagraph()->InsertRun(last_run, nullptr);
      }
      last_run->InsertCharacter(inserted, nullptr);
      
    } else {
      auto prev = selected->GetPrevRunCharacter();
      
      if( prev ) {
        selected->GetRun()->InsertCharacter(inserted, selected);
        
      } else {
        auto prev_run = selected->GetRun()->GetPrevRun();
        if( prev_run ) {
          prev_run->InsertCharacter(inserted, nullptr);
        } else {
          selected->GetRun()->InsertCharacter(inserted, selected);
        }
      }
    }
  }

  return inserted_run;

}


// void BackSpaceWordInternal(Paragraph* paragraph)
// {
//   auto last_word = paragraph->GetLastWord();
//   if( last_word == nullptr ) {

//   } else {
//     auto prev_char = last_word->GetLastCharacter();
//     last_word->RemoveCharacter(prev_char);

//     if( last_word->GetFirstCharacter() == nullptr )
//       paragraph->RemoveWord(last_word);
//   }
// }

// Run* BackSpaceRunInternal(Paragraph* paragraph)
// {
//   auto last_run = paragraph->GetLastRun();
//   Run* ret = nullptr;
//   if( last_run == nullptr ) {

//   } else {
//     auto prev_char = last_run->GetLastCharacter();
//     last_run->RemoveCharacter(prev_char);

//     if( last_run->GetFirstCharacter() == nullptr ) {
//       paragraph->RemoveRun(last_run);
//       ret = last_run;
//     }
//   }

//   return ret;
// }

}

InsertCharCommand::InsertCharCommand(Character* inserted, Character* selected)
    : selected_(selected),
      inserted_(inserted),
      inserted_run_(nullptr)
{
  
}

InsertCharCommand::~InsertCharCommand()
{}

void InsertCharCommand::Apply() 
{
  // InsertWordInternal(character_, inserted_);
  std::cout << "insert char apply" << std::endl;
  inserted_run_ = Run::GetCachedRun();
  inserted_run_ = InsertRunInternal(inserted_, selected_, inserted_run_);
  selected_->GetParagraph()->CreateWords();
  Run::SetCachedRun(nullptr);
}

void InsertCharCommand::UnApply() 
{
  auto run = inserted_->GetRun();
  run->RemoveCharacter(inserted_);
  
  if( inserted_run_ ) {
    inserted_run_->GetParagraph()->RemoveRun(inserted_run_);
  }
  
  selected_->GetParagraph()->CreateWords();
  
  // std::cout << "unapply!!!!!!!!!!!!!!!!!!!!!!!" << inserted_->GetChar() << std::endl;
  // if( paragraph_ ) {
  //   std::cout << "remove word" << std::endl;
  //   BackSpaceWordInternal(paragraph_);
  //   std::cout << "remove run" << std::endl;
  //   BackSpaceRunInternal(paragraph_);
  //   std::cout << "complete" << std::endl;
  // }
}

void InsertCharCommand::ReApply() 
{
  InsertRunInternal(inserted_, selected_, inserted_run_);
  selected_->GetParagraph()->CreateWords();
  
  // if( paragraph_ ) {
  //   InsertWordInternal(paragraph_, inserted_);
  //   InsertRunInternal(paragraph_, inserted_);
  // }
}

}  // le

#include "ins_char_delegate.h"

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"

namespace le {

namespace {

void InsertWordInternal(Paragraph* paragraph, Character* character)
{
  auto last_word = paragraph->GetLastWord();
  
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);
    last_word->InsertCharacter(character, nullptr);
  } else {
    
    auto prev_char = last_word->GetLastCharacter();
    if( typeid(*character) == typeid(BasicCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if ( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
    } else if (typeid(*character) == typeid(SpaceCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
      
    } else {

    }
  }
}

void InsertRunInternal(Paragraph* paragraph, Character* character)
{
  auto cached = Run::GetCachedRun();
  if( cached ) {
    paragraph->InsertRun(cached, nullptr);
  }
  
  auto last_run =  paragraph->GetLastRun();

  if(last_run == nullptr) {
    last_run = new TextRun();
    paragraph->InsertRun(last_run, nullptr);
  }
  
  last_run->InsertCharacter(character, nullptr);

  Run::SetCachedRun(nullptr);
}


void BackSpaceWordInternal(Paragraph& paragraph)
{
  auto last_word = paragraph.GetLastWord();
  if( last_word == nullptr ) {

  } else {
    auto prev_char = last_word->GetLastCharacter();
    last_word->RemoveCharacter(prev_char);

    if( last_word->GetFirstCharacter() == nullptr )
      paragraph.RemoveWord(last_word);
  }
}

Run* BackSpaceRunInternal(Paragraph& paragraph)
{
  auto last_run = paragraph.GetLastRun();
  Run* ret = nullptr;
  if( last_run == nullptr ) {

  } else {
    auto prev_char = last_run->GetLastCharacter();
    last_run->RemoveCharacter(prev_char);

    if( last_run->GetFirstCharacter() == nullptr ) {
      paragraph.RemoveRun(last_run);
      ret = last_run;
    }
  }

  return ret;
}

}

InsCharDelegate::InsCharDelegate(Character* inserted) : char_(inserted)
{}
InsCharDelegate::~InsCharDelegate()
{}

void InsCharDelegate::Apply(Character* character, Paragraph* paragraph)
{
  if( paragraph ) {
    InsertWordInternal(paragraph, char_);
    InsertRunInternal(paragraph, char_);
  }
}

void InsCharDelegate::UnApply(Character* character, Paragraph* paragraph)
{
  if( paragraph ) {
    BackSpaceWordInternal(*paragraph);
    BackSpaceRunInternal(*paragraph);
  }
}

void InsCharDelegate::ReApply(Character* character, Paragraph* paragraph)
{
  if( paragraph ) {
    InsertWordInternal(paragraph, char_);
    InsertRunInternal(paragraph, char_);
  }
}

}  // le

#include "paragraph.h"

#include "model/word.h"
#include "model/character/enter_character.h"
#include "model/character/space_character.h"
#include "model/character/basic_character.h"

#include <algorithm>
#include <iostream>

namespace le {

Paragraph::Paragraph()
    : enter_run_(this),
      view_(*this)
{}

Paragraph::~Paragraph()
{}

void Paragraph::RemoveRun(Run* run)
{
  if( run != nullptr ) {
    runs_.Remove(run->GetIterator());
    
  }
}

void Paragraph::RemoveWord(Word* word)
{
  if( word != nullptr ) {
    words_.Remove(word->GetIterator());
  }
}


void Paragraph::InsertRun(Run* new_run, Run* ref_run)
{
  if( ref_run == nullptr ) {
    auto it = runs_.Append(new_run);
    new_run->SetIterator(it);

    // auto lastline = GetView().GetLastChild();
    // auto& newview = new_run->GetRunView();
    // lastline->AddChildAt(lastline->GetChildCount() - 1, &newview);
    
  } else {
    auto it = runs_.InsertBefore(new_run, ref_run->GetIterator());
    new_run->SetIterator(it);

    // auto& newview = new_run->GetRunView();
    // auto refview = ref_run->GetRunView();
    // auto refindex = refview.GetIndex();
    // refview.GetParent()->AddChildAt(refindex, &newview);
    
  }
  new_run->SetParagraph(this);

}
void Paragraph::InsertWord(Word* new_word, Word* ref_word)
{
  if( ref_word == nullptr ) {
    auto it = words_.Append(new_word);
    new_word->SetIterator(it);
  } else {
    auto it = words_.InsertBefore(new_word, ref_word->GetIterator());
    new_word->SetIterator(it);
  }
  new_word->SetParagraph(this);
}


void Paragraph::PrintWord()
{
  std::cout<< "Words : ";
  
  auto word = words_.GetFirstNode();

  for( ; word ; word = word->GetNextWord() )
  {
    auto ch = word->GetFirstCharacter();
    std::string str;
    for( ; ch ; ch = ch->GetNextWordCharacter() )
      str += ch->GetChar();

    std::cout<< "["<<str << "] ";
    
  }

  std::cout<< std::endl;
}


void Paragraph::PrintRun()
{
  std::cout<< "Runs : ";
  
  auto run = runs_.GetFirstNode();

  for( ; run ; run = run->GetNextRun() )
  {
    auto ch = run->GetFirstCharacter();
    std::string str;
    for( ; ch ; ch = ch->GetNextRunCharacter() )
      str += ch->GetChar();

    std::cout<< "["<<str << "] ";
    
  }

  std::cout<< std::endl;
}

void Paragraph::PrintInfo() {
  PrintRun();
  PrintWord();
}


Character* Paragraph::GetFirstCharacter()
{
  auto first_run = GetFirstRun();
  if( first_run ) {
    return first_run->GetFirstCharacter();
  } else {
    return GetLastCharacter();
  }
}

Character* Paragraph::GetLastCharacter()
{
  return GetEnterChar();
}


void Paragraph::CreateWords()
{
  while(GetFirstWord()){
    RemoveWord(GetFirstWord());
  }

  std::vector<Word*> words;
  words.push_back( new Word() );
  
  for( auto character = GetFirstCharacter() ;
       character != GetEnterChar() ;
       character = character->GetNextParagraphCharacter() ) {

    words.back()->InsertCharacter(character, nullptr);
    
    if( typeid(*character) == typeid(SpaceCharacter) ) {
      auto next = character->GetNextParagraphCharacter();
      if( typeid(*next) == typeid(BasicCharacter) ) {
        words.push_back( new Word() );
      }
    }
  }

  for( auto&& word : words ) {
    InsertWord(word, nullptr);
  }
}


}  // le

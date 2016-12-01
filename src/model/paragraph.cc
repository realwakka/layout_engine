#include "paragraph.h"

#include "model/word.h"

#include <algorithm>
#include <iostream>

namespace le {

Paragraph::Paragraph()
    : enter_run_(this)
{}

Paragraph::~Paragraph()
{}

void Paragraph::InsertRun(Run* new_run, Run* ref_run)
{
  if( ref_run == nullptr )
    runs_.Append(new_run);
  else
    runs_.InsertBefore(new_run, ref_run->GetIterator());

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
}


void Paragraph::PrintWord()
{
  auto word = words_.GetFirstNode();

  for( ; word ; word = word->GetNextWord() )
  {
    auto ch = word->GetFirstCharacter();
    std::string str;
    for( ; ch ; ch = ch->GetNextCharacter() )
    {
      str += ch->GetChar();
    }
    std::cout<< "["<<str << "]";
    
  }

}



}  // le

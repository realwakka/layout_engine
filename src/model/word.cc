#include "word.h"

#include "model/character/character.h"
#include "model/paragraph.h"

#include <algorithm>

namespace le {

Word::Word()
{}

Word::~Word()
{}

void Word::InsertCharacter(Character* character, Character* reference)
{
  if( reference == nullptr ) {
    auto it = chars_.Append(character);
    character->SetWordIterator(it);
  } else  {
    auto it = chars_.InsertBefore(character, reference->GetWordIterator());
    character->SetWordIterator(it);
  }
}

void Word::RemoveCharacter(Character* character)
{
  chars_.Remove(character->GetWordIterator());
}

Word* Word::GetPrevWord()
{
  return node_.GetPrev();
}

Word* Word::GetNextWord()
{
  return node_.GetNext();
}


void Word::Split(Character* character)
{
  if( character->GetWord() != this )
    throw std::exception();

  Word* word = new Word();
  for( Character* ch = GetFirstCharacter() ;
       ch != character ; ch = ch->GetNextCharacter() ) {
    RemoveCharacter(ch);
    word->InsertCharacter(ch, nullptr);
  }

  GetParagraph()->InsertWord(word, this);
}

}  // le

#include "word.h"

#include "model/character/character.h"

#include <algorithm>

namespace le {

Word::Word()
{}

Word::~Word()
{}

void Word::InsertCharacter(Character* character, Character* reference)
{
  if( reference == nullptr )
    chars_.Append(character);
  else
    chars_.InsertBefore(character, reference->GetWordIterator());
}

Word* Word::GetPrevWord()
{
  // auto words = GetParagraph()->GetWords();
}

void Word::Split(Character* character)
{
  //for( Character* ch = GetFirstWord() ; ch != character ; ch = ch->GetNextChar
}

}  // le

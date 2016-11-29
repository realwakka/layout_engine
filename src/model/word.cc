#include "word.h"

#include "model/character/character.h"

#include <algorithm>

namespace le {

Word::Word()
{}

Word::~Word()
{}

void Word::InsertBefore(Character* character, Character* reference)
{
  chars_.InsertBefore(character, reference);
}

Word* Word::GetPrevWord()
{
  // auto words = GetParagraph()->GetWords();
}

void Word::Split(Character* character)
{

}

}  // le

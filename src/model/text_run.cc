#include "text_run.h"

#include <algorithm>

#include "model/character/character.h"

namespace le {

TextRun::TextRun(std::string text)
        : text_(text)
{
  for( char c : text ) {
    chars_.push_back(new Character(c));
  }
}

TextRun::TextRun(Character* character)
{
  text_.push_back(character->GetChar());
  chars_.emplace_back(character);
}

TextRun::~TextRun()
{

}

}  // le

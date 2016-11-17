#include "text_run.h"

#include "character.h"

namespace le {

TextRun::TextRun(std::string text)
        : text_(text)
{
  for( char c : text ) {
    chars_.push_back(new Character(c));
  }
}

TextRun::~TextRun()
{

}

void TextRun::insertRun(Run* run)
{
  
}

void TextRun::insertText(std::string text, Character* character)
{
  auto it = std::find(chars_.begin(), chars_.end(), character);
  for( auto it = text.rbegin() ; it != text.rend() ; ++it ) {
    
  }
}

}  // le

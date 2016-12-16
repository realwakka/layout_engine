#include "word_view.h"

#include <iostream>

#include "model/word.h"
#include "model/character/character.h"

namespace le {

WordView::WordView(Word& word)
    : word_(word)
{}

WordView::~WordView()
{}

void WordView::Paint(const Canvas& canvas)
{
  std::cout << "WordViewPaint... ";
  for( auto ch = word_.GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() ) {
    std::cout << ch->GetChar();
  }
  std::cout<< std::endl;
}

}  // le

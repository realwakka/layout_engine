#include "word_view.h"

#include <iostream>

#include "model/word.h"
#include "model/character/character.h"

#include "graphic/canvas.h"

namespace le {

WordView::WordView(Word& word)
    : word_(word)
{}

WordView::~WordView()
{}

void WordView::Paint(Canvas& canvas)
{

  std::cout << "WordViewPaint... ";
  for( auto ch = word_.GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() ) {
    std::cout << ch->GetChar();
    canvas.DrawGlyph(0, 0, ch->GetGlyph());
  }
  std::cout<< std::endl;
}

}  // le

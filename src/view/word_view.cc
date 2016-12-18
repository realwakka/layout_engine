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

void WordView::Layout()
{
  SetY(0);

  auto word_index = 0;
  auto word_width = word_.GetWordWidth();
  for( ; word_index < GetChildCount() ; ++word_index )
    if( GetChildAt(word_index) == this )
      break;

  if( word_index == 0 ) {
    SetX(0);
  }
  else {
    auto prev = GetChildAt(word_index - 1);
    auto x = prev->GetY() + prev->GetWidth();
    if( x + word_width < GetParent()->GetWidth() ) {
      SetX(x);
    }
    else {
      //next line
      SetX(x);
    }
  }

  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Layout();
}

}  // le

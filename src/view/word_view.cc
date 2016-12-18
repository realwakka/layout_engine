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
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  auto x = 0;
  for( auto ch = word_.GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() ) {
    auto glyph = ch->GetGlyph();
    canvas.DrawGlyph(x, 0, glyph);
    x += glyph.GetAdvanceX();
  }

  canvas.Restore();
}

void WordView::Layout()
{
  SetY(0);
  SetWidth(word_.GetWordWidth());

  auto word_index = 0;
  auto word_width = word_.GetWordWidth();
  for( ; word_index < GetParent()->GetChildCount() ; ++word_index )
    if( GetParent()->GetChildAt(word_index) == this )
      break;

  if( word_index == 0 ) {
    SetX(0);
  }
  else {
    auto prev = GetParent()->GetChildAt(word_index - 1);
    auto x = prev->GetX() + prev->GetWidth();
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

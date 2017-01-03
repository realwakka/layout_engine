#include "word_view.h"

#include <iostream>

#include "model/word.h"
#include "model/character/character.h"

#include "graphic/canvas.h"
#include "view/line_view.h"

namespace le {

WordView::WordView(Word& word)
    : word_(word)
{
  
}

WordView::~WordView()
{}

void WordView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());
  
  int baseline = static_cast<LineView*>(GetParent())->GetBaseline();

  for( int i=0 ; i<GetChildCount() ; ++i )
    GetChildAt(i)->Paint(canvas);

  canvas.Restore();
}

int WordView::GetWordWidth() const
{
  auto width = 0;
  for(int i=0 ; i<GetChildCount() ; ++i ) {
    auto charview = static_cast<CharacterView*>(GetChildAt(i));
    width += charview->GetCharacterWidth();
  }
  return width;
}

int WordView::GetSpaceWidth() const
{
  auto width = 0;
  for(int i=0 ; i<GetChildCount() ; ++i ) {
    auto charview = static_cast<CharacterView*>(GetChildAt(i));
    width += charview->GetSpaceWidth();
  }
  return width;  
}

void WordView::Layout()
{
  SetY(0);
  //SetWidth(word_.GetWordWidth());
  SetHeight(word_.GetWordHeight());

  auto word_index = GetIndex();
  auto word_width = GetWordWidth();
  auto space_width = GetSpaceWidth();

  if( word_index == 0 ) {
    SetX(0);
    for( int i=0 ; i<GetChildCount() ; ++i )
      GetChildAt(i)->Layout();

    auto lastchild = GetChildAt(GetChildCount() - 1);
    SetWidth(lastchild->GetX() + lastchild->GetWidth());
  }
  else {
    auto prev = GetParent()->GetChildAt(word_index - 1);
    auto x = prev->GetX() + prev->GetWidth();
    if( x + word_width - space_width < GetParent()->GetWidth() ) {
      SetX(x);
      for( auto index = 0; index < GetChildCount() ; ++index )
        GetChildAt(index)->Layout();
      auto lastchild = GetChildAt(GetChildCount() - 1);
      SetWidth(lastchild->GetX() + lastchild->GetWidth());
    }
    else {
      //next line
      auto nextline = GetParent()->GetNextParent();
      view_util::MoveChildsToNewParent(this, nextline);
      return;
    }
  }

}

View* WordView::GetNextParent() const
{
  auto nextparent = GetParent()->GetNextParent();
  auto nextword = new WordView(word_);
  nextparent->AddChildAt(0, nextword);
  return nextword;
}

}  // le

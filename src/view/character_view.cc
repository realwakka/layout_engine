#include "character_view.h"

#include "model/character/character.h"

namespace le {


CharacterView::CharacterView(Character& character)
    : character_(character)
{
}

CharacterView::~CharacterView()
{
}


void CharacterView::Layout()
{
  SetWidth(character_.GetGlyph().GetAdvanceX());
  SetHeight(0); // TODO : set exact height
  SetY(0);
  
  auto prev = GetPrevSibling();
  auto usedwidth = 0;
  if( prev != nullptr )
    usedwidth = prev->GetX() + prev->GetWidth();

  int remain = GetParent()->GetWidth() - usedwidth;
  if( remain > GetWidth() ) {
    SetX(usedwidth);
  } else {
    auto nextparent = GetParent()->GetNextParent();
    view_util::MoveChildsToNewParent(this, nextparent);
  }
}
void CharacterView::Paint(Canvas& canvas)
{

}

}  // le

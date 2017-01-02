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

  auto avail_width = GetAvailableWidth();
  auto prev = GetPrevSibling();
  auto usedwidth = 0;
  if( prev != nullptr )
    usedwidth = prev->GetX() + prev->GetWidth();

  // int remain = GetParent()->GetWidth() - usedwidth;
  if( avail_width >= GetWidth() ) {
    SetX(usedwidth);
  } else {
    auto nextparent = GetParent()->GetNextParent();
    view_util::MoveChildsToNewParent(this, nextparent);
  }
}
void CharacterView::Paint(Canvas& canvas)
{

}

int CharacterView::GetCharacterWidth() const
{
  return GetCharacter().GetGlyph().GetAdvanceX();
}
int CharacterView::GetSpaceWidth() const
{
  return 0;
}

}  // le

#include "character_view.h"

#include "model/character/character.h"
#include "graphic/canvas.h"
#include "view/line_view.h"

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
  view_util::SetHorizontalBlockPosition(this);
  SetWidth(character_.GetGlyph().GetAdvanceX());
  SetHeight(0); // TODO : set exact height
  SetY(0);
}
void CharacterView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  int baseline = static_cast<LineView*>(GetParent()->GetParent())->GetBaseline();

  auto glyph = GetCharacter().GetGlyph();
  canvas.DrawGlyph(Point(0, baseline), glyph);
  canvas.Restore();

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

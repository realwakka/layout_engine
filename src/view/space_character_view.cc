#include "space_character_view.h"

#include "model/character/space_character.h"
#include "view/line_view.h"
#include "graphic/canvas.h"

namespace le {

SpaceCharacterView::SpaceCharacterView(SpaceCharacter& space_character)
    : CharacterView(space_character)
{
  
}
SpaceCharacterView::~SpaceCharacterView()
{

}

void SpaceCharacterView::Layout()
{
  SetWidth(GetCharacter().GetGlyph().GetAdvanceX());
  SetHeight(0); // TODO : set exact height
  SetY(0);

  auto avail_width = GetAvailableWidth();
  auto prev = GetPrevSibling();
  auto usedwidth = 0;
  if( prev != nullptr )
    usedwidth = prev->GetX() + prev->GetWidth();

  SetX(usedwidth);
}
void SpaceCharacterView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  int baseline = static_cast<LineView*>(GetParent()->GetParent())->GetBaseline();

  auto glyph = GetCharacter().GetGlyph();
  canvas.DrawGlyph(Point(0, baseline), glyph);
  
  // for( auto index = 0; index < GetChildCount() ; ++index )
  //   GetChildAt(index)->Paint(canvas);

  canvas.Restore();
}

int SpaceCharacterView::GetCharacterWidth() const
{
  return GetCharacter().GetGlyph().GetAdvanceX();
}

int SpaceCharacterView::GetSpaceWidth() const
{
  return GetCharacter().GetGlyph().GetAdvanceX();
}

}  // le

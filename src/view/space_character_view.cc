#include "space_character_view.h"

#include "model/character/space_character.h"

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

}
void SpaceCharacterView::Paint(Canvas& canvas)
{

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

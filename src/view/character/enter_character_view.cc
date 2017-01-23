#include "view/character/enter_character_view.h"

#include "model/character/enter_character.h"
#include "graphic/canvas.h"
#include "graphic/paint.h"
#include "view/line_view.h"
#include <iostream>

namespace le {

namespace {
constexpr auto kViewSize = 20;
}

EnterCharacterView::EnterCharacterView(EnterCharacter& enter_character)
    : CharacterView(enter_character)
{}

EnterCharacterView::~EnterCharacterView()
{}

void EnterCharacterView::Layout()
{
  view_util::SetHorizontalBlockPosition(this);

  SetWidth(kViewSize);
  
  SetHeight(GetParent()->GetHeight());
}
void EnterCharacterView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  auto baseline = static_cast<LineView*>(GetParent())->GetBaseline();

  Point p1(0, baseline - GetHeight());
  Point p2(GetWidth(), baseline);

  le::Paint p;
  p.SetStyle(Paint::Style::kStroke);
  
  canvas.DrawRect(p1, p2, p);
  canvas.Restore();
}



}  // le

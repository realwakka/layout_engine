#include "view/character/enter_character_view.h"

#include "model/character/enter_character.h"
#include "graphic/canvas.h"
#include "graphic/paint.h"
#include "view/line_view.h"
#include "model/run.h"
#include "model/face/face_manager.h"
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

  auto& runprop = GetCharacter().GetRun()->GetRunProp();
  auto face = FaceManager::GetInstance()->GetFace(runprop);
  auto height = face.GetHeight();

  SetWidth(kViewSize);
  SetHeight(height);
}
void EnterCharacterView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  auto baseline = static_cast<LineView*>(GetParent())->GetBaseline();

  Point p1(0, 0);
  Point p2(GetWidth(), GetHeight());

  le::Paint p;
  p.SetStyle(Paint::Style::kStroke);
  
  canvas.DrawRect(p1, p2, p);
  canvas.Restore();
}

// bool EnterCharacterView::HitTest(HitItem& hititem, const Point& point)
// {
  
// }

}  // le

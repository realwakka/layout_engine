#include "single_underline.h"

#include "graphic/canvas.h"
#include "view/line_view.h"
#include "view/run/run_view.h"
#include "graphic/paint.h"

namespace le {

SingleUnderline::SingleUnderline()
{}
SingleUnderline::~SingleUnderline()
{}
  
void SingleUnderline::DrawUnderline(const RunView& runview, Canvas& canvas)
{
  auto baseline = static_cast<LineView*>(runview.GetParent())->GetBaseline();

  Point p1(0, baseline);
  Point p2(runview.GetWidth(), baseline);
  Paint paint;
  canvas.DrawLine(p1, p2, paint);
}


}  // le

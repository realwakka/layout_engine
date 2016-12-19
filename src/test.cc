#include "render_text.h"

int main()
{
  le::RenderText rendertext;
  rendertext.InsertText("this is test test test!");
  rendertext.Layout();
  rendertext.Paint();
}

#include "render_text.h"

int main()
{
  le::RenderText rendertext;
  rendertext.InsertText("this is ggtest!!");
  rendertext.Layout();
  rendertext.Paint();
  
}

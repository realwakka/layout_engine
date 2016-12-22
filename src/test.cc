#include "render_text.h"

#include <string>

int main(int argc, char* argv[])
{
  std::string text;
  if( argc == 1 ) {
    text = "Welcome to Realwakka's LayoutEngine project!";
  }
  else {
    text = argv[1];
  }
  le::RenderText rendertext;
  rendertext.InsertText(text);
  rendertext.Layout();
  rendertext.Paint();
}

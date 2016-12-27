#include "render_text.h"

#include <string>

int main(int argc, char* argv[])
{
  std::string text;
  if( argc == 1 ) {
    text = "Welcome to";
  }
  else {
    text = argv[1];
  }
  le::RenderText rendertext;
  rendertext.SetBold(true);
  rendertext.InsertText(text);
  rendertext.SetBold(false);

  rendertext.InsertText("asdf");
  
  rendertext.Layout();
  rendertext.Paint();
}

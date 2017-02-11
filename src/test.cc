#include "render_text.h"

#include <sys/un.h>
#include <string>
#include "controller/event/key_event.h"
#include "controller/event/keyboard_codes.h"

int main(int argc, char* argv[])
{
  std::string text;
  if( argc == 1 ) {
    // text = R"(A paragraph (from the Ancient Greek paragraphos, "to write beside" or "written beside") is a self-contained unit of a discourse in writing dealing with a particular point or idea. A paragraph consists of one or more sentences.[1][2] Though not required by the syntax of any language, paragraphs are usually an expected part of formal writing, used to organize longer prose.Welcome to)";
    text = "asdf";
  }
  else {
    text = argv[1];
  }
  le::RenderText rendertext;
  // rendertext.SetBold(true);
  // rendertext.SetSize(30);
  rendertext.InsertText(text);
  
  
  le::KeyEvent keyevent;
  keyevent.SetCode(le::KeyboardCode::VKEY_LEFT);
  rendertext.OnKeyDown(keyevent);
  
  rendertext.InsertText("a");

  
  // rendertext.UnDo();
  // rendertext.ReDo();
  // rendertext.SetSize(15);
  // rendertext.InsertText(text);
  // // rendertext.SetBold(false);
  // // rendertext.InsertText("asdf");
  rendertext.Layout();
  rendertext.UnDo();
  rendertext.WriteBitmapFile("output.bmp");

  
}

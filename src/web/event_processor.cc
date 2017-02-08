#include "event_processor.h"

#include <jsoncpp/json/json.h>
#include <iostream>

#include "controller/event/mouse_event.h"
#include "controller/event/key_event.h"
#include "render_text.h"

namespace le {
namespace web {

EventProcessor::EventProcessor()
{}

EventProcessor::~EventProcessor()
{}

bool EventProcessor::ProcessEvent(const std::string& json, RenderText& rendertext)
{
  Json::Value root;
  Json::Reader reader;

  if( !reader.parse(json, root) )
    return false;

  auto event_type = root.get("type", "" ).asString();
  if( event_type == "keypress" ) {
    // auto key = root.get("key", "" ).asString();
    // std::cout << "received key : " <<key<< std::endl;
    // rendertext.InsertText(key);
    // rendertext.Layout();
    // return true;
    
  } else if( event_type == "keydown" ) {
    auto code = root.get("keyCode", "" ).asInt();
    auto ctrl = root.get("ctrlKey", "false" ).asBool();
    auto alt = root.get("altKey", "false" ).asBool();
    auto shift = root.get("shiftKey", "false" ).asBool();

    std::cout << "keydown : " << code << std::endl;
    
    le::KeyEvent keyevent;
    auto str = root.get("key", "" ).asString();
    if( str.length() == 1 )
      keyevent.SetChar(str[0]);
    
    keyevent.SetCode(static_cast<le::KeyboardCode>(code));
    keyevent.SetCtrlDown(ctrl);
    keyevent.SetAltDown(alt);
    keyevent.SetShiftDown(shift);

    std::cout << "before  : " << code << std::endl;
    
    rendertext.OnKeyDown(keyevent);

    std::cout << "layout  : " << code << std::endl;
    rendertext.Layout();
    return true;
    
  } else if ( event_type == "mousedown" ) {
    
    auto x = root.get("x", "0" ).asInt();
    auto y = root.get("y", "0" ).asInt();

    le::MouseEvent event;
    event.SetX(x);
    event.SetY(y);

    rendertext.OnMousePressed(event);
    return false;
  }
}

}  // web
}  // le


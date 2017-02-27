#include "event_processor.h"

#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include "controller/event/mouse_event.h"
#include "controller/event/key_event.h"
#include "render_text.h"
#include "painter.h"

namespace le {
namespace web {

namespace {

bool ProcessEvent(const std::string& json, RenderText& rendertext, lws* wsi)
{
  Json::Value root;
  Json::Reader reader;

  if( !reader.parse(json, root) )
    return false;

  auto event_type = root.get("type", "" ).asString();
  if( event_type == "keypress" ) {
    
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
  } else if( event_type == "paint" ) {
    Painter painter;
    auto out =  painter.PaintToPng(rendertext);
    // std::ofstream ofs("output.png");
    // ofs.write(out.data(), out.size());
    // ofs.close();
    
    // std::unique_ptr<unsigned char[]> send_data(new unsigned char[LWS_PRE + out.size()]);
    auto data = new unsigned char[LWS_PRE + out.size()];
    std::memset(data, 0, LWS_PRE + out.size());
    std::memcpy(&data[LWS_PRE], out.data(), out.size());
    auto result = lws_write(wsi, &data[LWS_PRE], out.size(), LWS_WRITE_BINARY);
    std::cout << "paint result : " << result << std::endl;
    
    // std::memcpy(&send_data.get()[LWS_PRE], out.data(), out.size());
    // lws_write(wsi, (unsigned char*)&send_data.get()[LWS_PRE], out.size(), LWS_WRITE_BINARY);

  }
  return true;
}

}

EventProcessor::EventProcessor(lws* wsi)
    : running_(true),
      empty_(true),
      wsi_(wsi)
{
  event_executor_ = new std::thread([this]() {
      while( running_ ) {
        if( !event_queue_.empty() ) {
          auto&& json = event_queue_.front();
          ProcessEvent(json, rendertext_, wsi_);
	  processing_ = true;
          event_queue_.pop();
	  processing_ = false;
        }
      }
    });
}


EventProcessor::~EventProcessor()
{
  empty_ = false;
  running_ = false;
  event_executor_->join();
}

bool EventProcessor::PushEvent(const std::string& str)
{
  while( processing_ == true );
  event_queue_.push(str);
  // while( processing_ == false ) {
    
  // }
}

}  // web
}  // le


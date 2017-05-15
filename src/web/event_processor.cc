#include "event_processor.h"

#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

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
    keyevent.SetFlag(kControlDown,ctrl);
    keyevent.SetFlag(kAltDown,alt);
    keyevent.SetFlag(kShiftDown,shift);

    rendertext.OnKeyDown(keyevent);
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
    std::ofstream ofs("output.png");
    ofs.write(reinterpret_cast<char*>(out.data()), out.size());
    ofs.close();
    
    out.insert(out.begin(), LWS_PRE, 0);
    auto result = lws_write(wsi, out.data() + LWS_PRE, out.size() - LWS_PRE, LWS_WRITE_BINARY);
    std::cout << "paint result : " << result << std::endl;

  } else if( event_type == "fontsize" ) {
    auto size = std::stoi(root.get("size", "0" ).asString());
    rendertext.SetSize(size);
    rendertext.Layout();
  }
  return true;
}

}

EventProcessor::EventProcessor(lws* wsi)
    : running_(true),
      wsi_(wsi),
      event_executor_([this]() {
          while( running_ ) {
            std::unique_lock<std::mutex> lk(mutex_);
            if( event_queue_.empty() )
              cv_.wait(lk, [this]{ return !event_queue_.empty(); });
            auto json = event_queue_.front();
            event_queue_.pop();
            ProcessEvent(json, rendertext_, wsi_);
          }
        })
{
}


EventProcessor::~EventProcessor()
{
  running_ = false;
  event_executor_.join();
}

bool EventProcessor::PushEvent(const std::string& str)
{
  std::lock_guard<std::mutex> lk(mutex_);  
  event_queue_.push(str);
  cv_.notify_all();
}

}  // web
}  // le


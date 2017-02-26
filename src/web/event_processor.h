#ifndef LE_WEB_EVENT_PROCESSOR_H_
#define LE_WEB_EVENT_PROCESSOR_H_

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <libwebsockets.h>

#include "render_text.h"

namespace le {

class RenderText;

namespace web {

class EventProcessor
{
 public:
  EventProcessor(lws* wsi);
  virtual ~EventProcessor();

  bool PushEvent(const std::string& str);
  // RenderText& GetRenderText() { return rendertext_; }
  // void Loop();

 private:
  std::queue<std::string> event_queue_;
  RenderText rendertext_;
  std::thread* event_executor_;
  bool running_;
  std::atomic<bool> empty_;
  std::atomic<bool> processing_;
  lws* wsi_;
};


}  // web
}  // le

#endif /* LE_WEB_EVENT_PROCESSOR_H_ */

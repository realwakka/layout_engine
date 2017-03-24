#ifndef LE_WEB_EVENT_PROCESSOR_H_
#define LE_WEB_EVENT_PROCESSOR_H_

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
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

 private:
  std::queue<std::string> event_queue_;
  RenderText rendertext_;
  std::thread* event_executor_;
  bool running_;
  lws* wsi_;
  std::condition_variable cv_;
  std::mutex mutex_;
};


}  // web
}  // le

#endif /* LE_WEB_EVENT_PROCESSOR_H_ */

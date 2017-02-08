#ifndef LE_WEB_EVENT_PROCESSOR_H_
#define LE_WEB_EVENT_PROCESSOR_H_

#include <string>

namespace le {

class RenderText;

namespace web {

class EventProcessor
{
 public:
  EventProcessor();
  virtual ~EventProcessor();

  bool ProcessEvent(const std::string& str, RenderText& rendertext);
};


}  // web
}  // le

#endif /* LE_WEB_EVENT_PROCESSOR_H_ */

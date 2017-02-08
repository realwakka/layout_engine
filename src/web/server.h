#ifndef LE_WEB_SERVER_H_
#define LE_WEB_SERVER_H_

#include <unordered_map>
#include "render_text.h"
#include <libwebsockets.h>

namespace le {
namespace web {

class Server
{
 public:
  Server();
  virtual ~Server();

  void Start();

 private:
  std::unordered_map<lws*, RenderText*> rendertext_map_;

};


}  // web
}  // le

#endif /* LE_WEB_SERVER_H_ */

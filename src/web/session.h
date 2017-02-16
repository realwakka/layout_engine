#ifndef LE_SESSION_H_
#define LE_SESSION_H_

#include "render_text.h"
#include <libwebsockets.h>

namespace le {
namespace web {

class Session
{
 public:
  Session();
  virtual ~Session();

  void Start();

 private:
  RenderText rendertext_;
};

}  // web
}  // le


#endif /* LE_SESSION_H_ */

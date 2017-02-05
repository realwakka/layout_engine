#ifndef LE_WEB_SERVER_H_
#define LE_WEB_SERVER_H_

namespace le {
namespace web {

class Server
{
 public:
  Server();
  virtual ~Server();

  void Start();
};


}  // web
}  // le

#endif /* LE_WEB_SERVER_H_ */

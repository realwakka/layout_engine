#ifndef LE_SELECTION_H_
#define LE_SELECTION_H_

#include <memory>

namespace le {

class Controller;
class View;
class RenderText;

class Selection : public std::enable_shared_from_this<Selection>
{
 public:
  virtual View& GetView() = 0;

};

}  // le

#endif /* LE_SELECTION_H_ */

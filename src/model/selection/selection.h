#ifndef LE_SELECTION_H_
#define LE_SELECTION_H_

#include <memory>

namespace le {

class Controller;
class SelectionView;

class Selection
{
 public:
  virtual std::unique_ptr<Controller> GetController() const = 0;
  virtual SelectionView& GetSelectionView() const = 0;
  
};

}  // le

#endif /* LE_SELECTION_H_ */

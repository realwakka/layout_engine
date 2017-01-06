#ifndef LE_CARET_SELECTION_VIEW_H_
#define LE_CARET_SELECTION_VIEW_H_

#include "view/view.h"

namespace ls {

class CaretSelectionView : public View
{
 public:
  CaretSelectionView(CaretSelection& caret_selection);
  virtual ~CaretSelectionView();

 private:
  CaretSelection& caret_selection_;
};


}  // ls


#endif /* LE_CARET_SELECTION_VIEW_H_ */


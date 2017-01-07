#ifndef LE_CARET_SELECTION_VIEW_H_
#define LE_CARET_SELECTION_VIEW_H_

#include "view/view.h"

namespace le {

class CaretSelection;

class CaretSelectionView : public View
{
 public:
  CaretSelectionView(CaretSelection& caret_selection);
  virtual ~CaretSelectionView();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;


 private:
  CaretSelection& caret_selection_;
};


}  // le


#endif /* LE_CARET_SELECTION_VIEW_H_ */


#ifndef LE_BLOCK_SELECTION_VIEW_H_
#define LE_BLOCK_SELECTION_VIEW_H_

#include "view/view.h"

namespace le {

class BlockSelectionView : public View
{
 public:
  BlockSelectionView();
  virtual ~BlockSelectionView();

  void Layout() override;
  void Paint(Canvas& canvas) override;
  
};


}  // le

#endif /* LE_BLOCK_SELECTION_VIEW_H_ */

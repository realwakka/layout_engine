#ifndef LE_BLOCK_SELECTION_VIEW_H_
#define LE_BLOCK_SELECTION_VIEW_H_

#include "view/view.h"
#include <memory>

namespace le {

class BlockSelection;

class BlockSelectionView : public View
{
 public:
  BlockSelectionView(BlockSelection& block_selection);
  virtual ~BlockSelectionView();

  void Layout() override;
  void Paint(Canvas& canvas) override;

 private:
  BlockSelection& block_selection_;
  
};


}  // le

#endif /* LE_BLOCK_SELECTION_VIEW_H_ */

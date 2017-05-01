#ifndef LE_BLOCK_SELECTION_H_
#define LE_BLOCK_SELECTION_H_

#include "model/selection/selection.h"
#include "view/selection/block_selection_view.h"

namespace le {

class Character;

class BlockSelection : public Selection
{
 public:
  BlockSelection(Character& start, Character& end);
  virtual ~BlockSelection();

  std::unique_ptr<Controller> GetController(RenderText* rendertext) const override;
  View& GetView() override;

 private:
  Character& start_;
  Character& end_;
  BlockSelectionView view_;

};


}  // le

#endif /* LE_BLOCK_SELECTION_H_ */

#ifndef LE_CARET_SELECTION_H_
#define LE_CARET_SELECTION_H_

#include "model/selection/selection.h"

namespace le {

class Character;

class CaretSelection : public Selection
{
 public:
  CaretSelection(Character& character);
  virtual ~CaretSelection();

  virtual std::unique_ptr<Controller> GetController() const override;
  virtual SelectionView& GetSelectionView() const override;

  Character& GetCharacter() { return character_; }

 private:
  Character& character_;
  
};


}  // le

#endif /* LE_CARET_SELECTION_H_ */

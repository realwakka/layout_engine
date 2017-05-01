#ifndef LE_CARET_SELECTION_H_
#define LE_CARET_SELECTION_H_

#include "model/selection/selection.h"
#include "view/selection/caret_selection_view.h"

namespace le {

class Character;

class CaretSelection : public Selection
{
 public:
  CaretSelection(Character& character);
  virtual ~CaretSelection();

  std::unique_ptr<Controller> GetController(RenderText* rendertext) const override;
  View& GetView() override;

  Character& GetCharacter() { return character_; }

 private:
  Character& character_;
  CaretSelectionView view_;
  
};


}  // le

#endif /* LE_CARET_SELECTION_H_ */

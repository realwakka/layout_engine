#ifndef LE_CARET_SELECTION_H_
#define LE_CARET_SELECTION_H_

#include "model/selection/selection.h"
#include "view/selection/caret_selection_view.h"
#include "controller/event/mouse_event.h"

namespace le {

class Character;

class CaretSelection : public Selection
{
 public:
  CaretSelection(Character& character, int x);
  explicit CaretSelection(Character& character);
  virtual ~CaretSelection();

  View& GetView() override;
  const CaretSelectionView* GetCaretView() const { return &view_; }

  Character& GetCharacter() { return character_; }

  int GetX() const { return x_; }
  void SetX(int x) { x_ = x; }

 private:
  Character& character_;
  CaretSelectionView view_;
  int x_;
  
};


}  // le

#endif /* LE_CARET_SELECTION_H_ */

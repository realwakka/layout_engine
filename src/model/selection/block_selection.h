#ifndef LE_BLOCK_SELECTION_H_
#define LE_BLOCK_SELECTION_H_

#include "model/selection/selection.h"
#include "view/selection/block_selection_view.h"

namespace le {

class Character;

enum class CaretPosition
{
  kStart, kEnd
};

class BlockSelection : public Selection
{
 public:
  BlockSelection(Character& start, Character& end, CaretPosition pos);
  virtual ~BlockSelection();

  View& GetView() override;

  Character* GetStart() const { return &start_; }
  Character* GetEnd() const { return &end_; }
  Character* GetCaret() const;
  Character* GetTail() const;
  CaretPosition GetCaretPosition() const { return pos_; }

  int GetX() const { return x_; }

 private:
  Character& start_;
  Character& end_;
  CaretPosition pos_;
  BlockSelectionView view_;
  int x_;

};


}  // le

#endif /* LE_BLOCK_SELECTION_H_ */

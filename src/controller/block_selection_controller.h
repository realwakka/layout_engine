#ifndef LE_BLOCK_SELECTION_CONTROLLER_H_
#define LE_BLOCK_SELECTION_CONTROLLER_H_

#include "controller/controller.h"
#include "model/selection/block_selection.h"

namespace le {

class RenderText;
class Character;

class BlockSelectionController : public Controller
{
 public:
  BlockSelectionController(RenderText& rendertext, Character& begin, Character& end, CaretPosition pos);
  virtual ~BlockSelectionController();

  void InsertText(std::string text) override;
  void BackSpaceChar() override;
  void SetBold(bool bold)  override;
  void SetItalic(bool italic)  override;
  void SetSize(int size)  override;
  void InsertChar(Character* character) override;
  void SetPageSize(int width, int height) override;
  
  void OnMousePressed(const MouseEvent& event) override;
  void OnKeyDown(const KeyEvent& event) override;
  
  void Paint(Canvas& canvas) override;
  void Layout() override;
  
 private:
  RenderText& rendertext_;
  BlockSelection selection_;
  
};


}  // le

#endif /* LE_BLOCK_SELECTION_CONTROLLER_H_ */

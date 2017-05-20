#ifndef LE_CARET_CONTROLLER_H_
#define LE_CARET_CONTROLLER_H_

#include "controller/controller.h"
#include "model/selection/caret_selection.h"

namespace le {

class Character;
class RenderText;

class CaretController : public Controller
{
 public:
  CaretController(Character& character, int x, RenderText* rendertext);
  CaretController(Character& character, RenderText* rendertext);
  virtual ~CaretController();

 public:
  void InsertText(std::string text) override;
  void InsertChar(Character* character) override;
  void BackSpaceChar() override;
  
  void SetBold(bool bold) override;
  void SetItalic(bool italic) override;
  void SetSize(int size) override;
  void SetPageSize(int width, int height) override;
  void OnMousePressed(const MouseEvent& event) override;
  void OnKeyDown(const KeyEvent& event) override;

  void Paint(Canvas& canvas) override;
  void Layout() override;

 private:
  RenderText* rendertext_;
  CaretSelection selection_;
  

};


}  // le

#endif /* LE_CARET_CONTROLLER_H_ */

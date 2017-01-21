#ifndef LE_ENTER_CHAR_CONTROLLER_H_
#define LE_ENTER_CHAR_CONTROLLER_H_

#include "controller/controller.h"

namespace le {

class EnterCharacter;

class EnterCharController : public Controller
{
 public:
  EnterCharController(EnterCharacter& enter_char);
  virtual ~EnterCharController();

 public:
  void InsertText(std::string text) override;
  void InsertChar(Character* character) override;
  void BackSpaceChar() override;
  
  void SetBold(bool bold) override;
  void SetItalic(bool italic) override;
  void SetSize(int size) override;
  void SetPageSize(int width, int height) override;
  void OnMousePressed(const MouseEvent& event) override;

 private:
  EnterCharacter& enter_char_;

};


}  // le

#endif /* LE_ENTER_CHAR_CONTROLLER_H_ */

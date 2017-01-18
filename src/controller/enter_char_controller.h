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
  virtual void InsertText(std::string text) override;
  virtual void InsertChar(Character* character) override;
  virtual void SetBold(bool bold) override;
  virtual void SetItalic(bool italic) override;
  virtual void SetSize(int size) override;
  virtual void SetPageSize(int width, int height) override;

 private:
  EnterCharacter& enter_char_;

};


}  // le

#endif /* LE_ENTER_CHAR_CONTROLLER_H_ */

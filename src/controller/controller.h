#ifndef LE_CONTROLLER_H_
#define LE_CONTROLLER_H_

#include <string>
#include <memory>

namespace le {

class Character;
class MouseEvent;
class KeyEvent;
class Selection;
class Canvas;

class Controller : public std::enable_shared_from_this<Controller>
{
 public:
  virtual void InsertText(std::string text)  = 0;
  virtual void BackSpaceChar() = 0;
  virtual void SetBold(bool bold)  = 0;
  virtual void SetItalic(bool italic)  = 0;
  virtual void SetSize(int size)  = 0;
  virtual void InsertChar(Character* character) = 0;
  virtual void SetPageSize(int width, int height) = 0;
  
  virtual void OnMousePressed(const MouseEvent& event) = 0;
  virtual void OnKeyDown(const KeyEvent& event) = 0;

  //virtual const Selection* GetSelection() const = 0;

  virtual void Layout() = 0;
  virtual void Paint(Canvas& canvas) = 0;
};


}  // le

#endif /* LE_CONTROLLER_H_ */

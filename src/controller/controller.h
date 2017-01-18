#ifndef LE_CONTROLLER_H_
#define LE_CONTROLLER_H_

#include <string>

namespace le {

class Character;

class Controller
{
 public:
  virtual void InsertText(std::string text)  = 0;
  virtual void SetBold(bool bold)  = 0;
  virtual void SetItalic(bool italic)  = 0;
  virtual void SetSize(int size)  = 0;
  virtual void InsertChar(Character* character) = 0;
  virtual void SetPageSize(int width, int height) = 0;
};


}  // le

#endif /* LE_CONTROLLER_H_ */

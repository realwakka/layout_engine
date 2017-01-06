#ifndef LE_CONTROLLER_H_
#define LE_CONTROLLER_H_

namespace le {

class Controller
{
 public:
  virtual void InsertText(std::string text) const = 0;
  virtual void SetBold(bool bold) const = 0;
  virtual void SetItalic(bool italic) const = 0;
  virtual void SetSize(int size) const = 0;

};


}  // le

#endif /* LE_CONTROLLER_H_ */

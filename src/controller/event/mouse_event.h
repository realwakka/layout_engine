#ifndef LE_MOUSEEVENT_H_
#define LE_MOUSEEVENT_H_

namespace le {

class MouseEvent
{
 public:
  enum class Type {
    kLButton,
    kRButton
  };
 public:
  MouseEvent();
  virtual ~MouseEvent();

  int GetX() const { return x_; }
  void SetX(int x) { x_ = x; }

  int GetY() const { return y_; }
  void SetY(int y) { y_ = y; }

  Type GetType() const { return type_; }
  void SetType(Type type) { type_ = type; }
  

 private:
  int x_;
  int y_;
  Type type_;
  
};


}  // le

#endif /* LE_MOUSEEVENT_H_ */

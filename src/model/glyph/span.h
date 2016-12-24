#ifndef LE_SPAN_H_
#define LE_SPAN_H_

namespace le {

class Span
{
 public:
  Span(int x, int y, int length);
  virtual ~Span();

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetLength() const { return length_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  void SetLength(int length) { length_ = length; }
  
 private:
  int x_;
  int y_;
  int length_;
  
};


}  // le


#endif /* LE_SPAN_H_ */


#ifndef POINT_H_
#define POINT_H_

namespace le {

class Point
{
 public:
  Point();
  Point(int x, int y);
  virtual ~Point();

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

 private:
  int x_;
  int y_;
};

}  // le


#endif /* POINT_H_ */

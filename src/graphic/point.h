#ifndef POINT_H_
#define POINT_H_

namespace le {

class Matrix;

class Point
{
 public:
  Point();
  Point(int x, int y);
  Point(const Point& point);
  virtual ~Point();

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  Point Transform(const Matrix& matrix) const;

 private:
  int x_;
  int y_;
};

}  // le


#endif /* POINT_H_ */

#ifndef VIEW_H_
#define VIEW_H_

namespace le {

class View
{
 public:
  View();
  virtual ~View();

  void Layout();
  void Paint();

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  void SetWidth(int width) { width_ = width; }
  void SetHeight(int height) { height_ = height; }

 private:
  int width_;  
  int height_;
  int x_;
  int y_;

};


}  // le


#endif /* VIEW_H_ */


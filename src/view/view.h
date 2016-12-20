#ifndef VIEW_H_
#define VIEW_H_

#include <vector>

namespace le {

class Canvas;

class View
{
 public:
  View();
  virtual ~View();

  virtual void Layout();
  virtual void Paint(Canvas& canvas);

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  void SetWidth(int width) { width_ = width; }
  void SetHeight(int height) { height_ = height; }

  int GetChildCount() const { return childs_.size(); }
  View* GetChildAt(int index) const { return childs_[index]; }

  void AddChildAt(int index, View* view);
  void RemoveChildAt(int index);

  void SetParent(View* parent) { parent_ = parent; }
  View* GetParent() const { return parent_; }

  View* GetNextSibling() const;
  View* GetPrevSibling() const;

  int GetIndex() const;

  virtual View* GetNextParent() const { return nullptr; }

 private:
  int width_;  
  int height_;
  int x_;
  int y_;

  std::vector<View*> childs_;
  View* parent_;

};


}  // le


#endif /* VIEW_H_ */


#ifndef VIEW_H_
#define VIEW_H_

#include <vector>
#include "graphic/point.h"

namespace le {

class Canvas;
class Layer;
class HitItem;

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
  void AppendChild(View* view);
  View* RemoveChildAt(int index);

  void SetParent(View* parent) { parent_ = parent; }
  View* GetParent() const { return parent_; }

  View* GetNextSibling() const;
  View* GetPrevSibling() const;

  View* GetLastChild() const;
  View* GetFirstChild() const;

  int GetIndex() const;

  Point GetLocalPosition() const { return Point(x_,y_); }

  virtual int GetAvailableWidth() const;
  virtual View* GetNextParent() const { return nullptr; }

  Point GetAbsolutePosition() const;
  virtual Layer* GetLayer() { return GetParent()->GetLayer(); }
  virtual bool HitTest(HitItem& hititem, const Point& point);

 private:
  int width_;  
  int height_;
  int x_;
  int y_;

  std::vector<View*> childs_;
  View* parent_;

};

namespace view_util {

void SetVerticalBlockPosition(View* view);
void SetHorizontalBlockPosition(View* view);
void MoveChildsToNewParent(View* begin, View* newparent);
void LayoutChilds(View* view);
void PaintChilds(Canvas& canvas, View* view);
bool HitTestRect(const View* view, const Point& point);

}


}  // le


#endif /* VIEW_H_ */


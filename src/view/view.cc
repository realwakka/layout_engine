#include "view.h"

namespace le {

View::View()
    : width_(0),
      height_(0),
      x_(0),
      y_(0)
{}

View::~View()
{}

void View::Layout()
{}

void View::Paint(Canvas& canvas)
{}


void View::AddChildAt(int index, View* view)
{
  childs_.emplace(childs_.begin() + index, view);
  view->SetParent(this);
}

void View::RemoveChildAt(int index)
{
  auto it = childs_.erase(childs_.begin() + index);
  (*it)->SetParent(nullptr);
}

}  // le

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

View* View::GetNextSibling() const
{
  auto parent = GetParent();
  auto child_count = parent->GetChildCount();
  if( parent->GetChildAt(child_count - 1) == this ) {
    return nullptr;
  } else {
    auto index = 0;
    for(; index<parent->GetChildCount() ; ++index )
      if( parent->GetChildAt(index) == this )
        break;

    return parent->GetChildAt(index + 1);
  }
}

View* View::GetPrevSibling() const
{
  auto parent = GetParent();
  if( parent->GetChildAt(0) == this ) {
    return nullptr;
  } else {
    auto index = parent->GetChildCount();
    for(; index > -1 ; --index )
      if( parent->GetChildAt(index) == this )
        break;

    return parent->GetChildAt(index - 1);
  }
  
}


}  // le

#include "view.h"

namespace le {

View::View()
    : width_(0),
      height_(0),
      x_(0),
      y_(0),
      parent_(nullptr)
{}

View::~View()
{}

void View::Layout()
{}

void View::Paint(Canvas& canvas)
{}


void View::AddChildAt(int index, View* view)
{
  if( view == nullptr )
    throw std::exception();
  
  childs_.emplace(childs_.begin() + index, view);
  view->SetParent(this);
}

View* View::RemoveChildAt(int index)
{
  auto removed = childs_[index];
  childs_.erase(childs_.begin() + index);
  removed->SetParent(nullptr);
  return removed;
}

View* View::GetNextSibling() const
{
  auto parent = GetParent();
  auto child_count = parent->GetChildCount();
  if( parent->GetChildAt(child_count - 1) == this ) {
    return nullptr;
  } else {
    auto index = GetIndex();
    return parent->GetChildAt(index - 1);
  }
}

View* View::GetPrevSibling() const
{
  auto parent = GetParent();
  if( parent->GetChildAt(0) == this ) {
    return nullptr;
  } else {
    auto index = GetIndex();
    return parent->GetChildAt(index - 1);
  }
}

int View::GetIndex() const
{
  auto index = 0;
  for( ; index < GetParent()->GetChildCount() ; ++index )
    if( GetParent()->GetChildAt(index) == this )
      break;
  return index;
}

int View::GetAvailableWidth() const
{
  if( GetParent() ) {
    auto prev = GetPrevSibling();
    if( prev ) {
      return GetParent()->GetAvailableWidth() - ( prev->GetX() + prev->GetWidth() );
    }else {
      return GetParent()->GetAvailableWidth();
    }
  } else {
    return GetWidth();
  }
}

namespace view_util {

void MoveChildsToNewParent(View* begin, View* newparent)
{
  auto oldparent = begin->GetParent();
  auto index = begin->GetIndex();
  while( true ) {
    auto count = oldparent->GetChildCount();
    if( index > count - 1 )
      break;
    auto removed = oldparent->RemoveChildAt(count - 1);
    newparent->AddChildAt(0, removed);
  }
}

}

}  // le

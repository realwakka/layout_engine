#include "view.h"

#include "view/hititem.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

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

void View::AppendChild(View* view)
{
  AddChildAt(GetChildCount(), view);
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

View* View::GetLastChild() const
{
  if( childs_.empty() )
    return nullptr;
  else
    return childs_[childs_.size() - 1];
}

View* View::GetFirstChild() const
{
  if( childs_.empty() )
    return nullptr;
  else
    return childs_[0];
}

Point View::GetAbsolutePosition() const
{
  auto x = 0;
  auto y = 0;
  auto view = this;
  while( view ) {
    x += view->GetX();
    y += view->GetY();
    view = view->GetParent();
  }

  return Point(x,y);
}


bool View::HitTest(HitItem& hititem, const Point& point)
{
  if( view_util::HitTestRect(this, point) ) {
    hititem.SetView(this);
    // std::for_each(childs_.begin(), childs_.end(),
    //          [&hititem, &point](View* view)
    //               { view->HitTest(hititem, point + view->GetLocalPosition()); });

    std::cout << "success hit : " << typeid(*this).name() << std::endl;
    return true;
  } else {
    return false;
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

void SetVerticalBlockPosition(View* view)
{
  auto prev = view->GetPrevSibling();
  if( prev ) {
    view->SetX(prev->GetX());
    view->SetY(prev->GetY() + prev->GetHeight());
  } else {
    view->SetX(0);
    view->SetY(0);
  }
  
}

void SetHorizontalBlockPosition(View* view)
{
  auto prev = view->GetPrevSibling();
  if( prev ) {
    view->SetX(prev->GetX() + prev->GetWidth());
    view->SetY(prev->GetY());
  } else {
    view->SetX(0);
    view->SetY(0);
  }
}

void LayoutChilds(View* view)
{
  for( int i=0 ; i<view->GetChildCount(); i++ )
    view->GetChildAt(i)->Layout();
}

void PaintChilds(Canvas& canvas, View* view)
{
  for( int i=0 ; i<view->GetChildCount(); i++ )
    view->GetChildAt(i)->Paint(canvas);
}

bool HitTestRect(const View* view, const Point& point)
{
  return point.GetX() >= 0 && point.GetY() >= 0 &&
    point.GetX() < view->GetWidth() && point.GetY() < view->GetHeight();
}


}

}  // le

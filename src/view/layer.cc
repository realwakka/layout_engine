#include "layer.h"

#include "view/view.h"

namespace le {

namespace {

bool HitTestView(View* view, HitItem& hititem, const Point& point)
{
  if( view->HitTest(hititem, point) ) {
    for( int i=0 ; i<view->GetChildCount() ; ++i ) {
      auto child = view->GetChildAt(i);
      Point child_point( point.GetX() - child->GetX(), point.GetY() - child->GetY());
      auto result = HitTestView(view->GetChildAt(i), hititem, child_point);
      if( result )
        return true;
    }
  }

  return false;
}

}

Layer::Layer(View* view)
    : view_(view),
      negative_(nullptr),
      positive_(nullptr),
      parent_(nullptr)
{}
Layer::~Layer()
{}

Layer* Layer::SetPositiveLayer(Layer* layer)
{
  layer->parent_ = this;
  positive_ = layer;
}
Layer* Layer::SetNegativeLayer(Layer* layer)
{
  layer->parent_ = this;
  negative_ = layer;
}


bool Layer::HitTest(HitItem& hititem, const Point& point) const
{
  auto result = false;

  if( positive_->HitTest(hititem, point) ) {
    return true;
  } else {
    result = HitTestView(view_, hititem, point);
    
    if( !result && negative_ )
      result = negative_->HitTest(hititem, point);
    
  }
  
  return result;
}

}  // le

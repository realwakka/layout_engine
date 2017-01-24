#ifndef LE_LAYER_H_
#define LE_LAYER_H_

#include "type/container.h"

namespace le {

class View;
class HitItem;
class Point;

class Layer
{
 public:
  Layer(View* view);
  virtual ~Layer();

  Layer* GetPositiveLayer() const { return positive_; }
  Layer* GetNegativeLayer() const { return negative_; }

  Layer* SetPositiveLayer(Layer* layer);
  Layer* SetNegativeLayer(Layer* layer);

  void GetParentLayer(Layer* parent) { parent_ = parent; }
  View* GetView() { return view_; }

  bool HitTest(HitItem& hititem, const Point& point) const;
  
 private:
  // Parent<Layer,Layer> parent_;
  // Child<Layer,Layer> child_;
  View* view_;

  Layer* positive_;
  Layer* negative_;
  Layer* parent_;
  
};


}  // le

#endif /* LE_LAYER_H_ */

#ifndef LE_HITITEM_H_
#define LE_HITITEM_H_

namespace le {

class View;

class HitItem
{
 public:
  HitItem();
  virtual ~HitItem();

  View* GetView() const { return view_; }
  void SetView(View* view) { view_ = view; }

 private:
  View* view_;
  
  
};


}  // le

#endif /* LE_HITITEM_H_ */

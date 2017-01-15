#ifndef LE_PAGEVIEW_H_
#define LE_PAGEVIEW_H_

#include "view/view.h"
#include "util/conv_util.h"
#include "model/prop/section_prop.h"

namespace le {

class SectionProp;

class PageView : public View
{
 public:
  PageView(SectionProp& section_prop);
  virtual ~PageView();
 
  virtual void Layout();
  virtual void Paint(Canvas& canvas);

  int GetTopMargin() const { conv_util::Twip2Pixel(section_prop_.GetPageMargin().GetTop()); }
  int GetBottomMargin() const { conv_util::Twip2Pixel(section_prop_.GetPageMargin().GetBottom()); }
  int GetRightMargin() const { conv_util::Twip2Pixel(section_prop_.GetPageMargin().GetRight()); }
  int GetLeftMargin() const { conv_util::Twip2Pixel(section_prop_.GetPageMargin().GetLeft()); }

 private:
  SectionProp& section_prop_;

};


}  // le

#endif /* LE_PAGEVIEW_H_ */




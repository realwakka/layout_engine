#ifndef LE_PAGEVIEW_H_
#define LE_PAGEVIEW_H_

#include "view/view.h"

namespace le {

class SectionProp;

class PageView : public View
{
 public:
  PageView(SectionProp& section_prop);
  virtual ~PageView();

 private:
  SectionProp& section_prop_;

};


}  // le

#endif /* LE_PAGEVIEW_H_ */




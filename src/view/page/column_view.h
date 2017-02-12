#ifndef LE_COLUMN_VIEW_H_
#define LE_COLUMN_VIEW_H_

#include "view/view.h"

namespace le {

class ColumnView : public View
{
 public:
  ColumnView();
  virtual ~ColumnView();

  void Layout() override;
  void Paint(Canvas& canvas) override;
  
};


}  // le

#endif /* LE_COLUMN_VIEW_H_ */

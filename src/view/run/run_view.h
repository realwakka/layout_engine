#ifndef LE_RUN_VIEW_H_
#define LE_RUN_VIEW_H_

#include "view/view.h"

namespace le {

class Run;

class RunView : public View
{
 public:
  RunView(Run& run);
  virtual ~RunView();

  virtual void Layout();
  virtual void Paint(Canvas& canvas);
  virtual View* GetNextParent() const;

  Run& GetRun() const { return run_; }
 public:
  Run& run_;
};


}  // le

#endif /* LE_RUN_VIEW_H_ */

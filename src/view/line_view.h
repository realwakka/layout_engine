#ifndef LE_LINE_VIEW_H_
#define LE_LINE_VIEW_H_

#include <vector>
#include "view/view.h"

namespace le {

class WordView;

class LineView : public View
{
 public:
  LineView();
  virtual ~LineView();

  virtual void Paint(Canvas& canvas) override;
  virtual void Layout() override;

  virtual View* GetNextParent() const override;

  void SetBaseline(int baseline) { baseline_ = baseline; }
  int GetBaseline() const { return baseline_; }

  virtual int GetAvailableWidth() const;

 private:
  int baseline_;

};


}  // le

#endif /* LE_LINE_VIEW_H_ */

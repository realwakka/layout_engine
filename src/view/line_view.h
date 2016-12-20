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

 private:
  std::vector<WordView*> word_views_;

};


}  // le

#endif /* LE_LINE_VIEW_H_ */

#ifndef LE_NORMAL_WORD_VIEW_DELEGATE_H_
#define LE_NORMAL_WORD_VIEW_DELEGATE_H_

#include "view/word_view_delegate.h"

namespace le {

class NormalWordViewDelegate : public WordViewDelegate
{
 public:
  NormalWordViewDelegate(WordView& word_view);
  virtual ~NormalWordViewDelegate();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;
};


}  // le

#endif /* LE_NORMAL_WORD_VIEW_DELEGATE_H_ */

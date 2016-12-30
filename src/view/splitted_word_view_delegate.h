#ifndef LE_SPLITTED_WORD_VIEW_DELEGATE_H_
#define LE_SPLITTED_WORD_VIEW_DELEGATE_H_

#include "view/word_view_delegate.h"

namespace le {

class SplittedWordViewDelegate : public WordViewDelegate
{
 public:
  SplittedWordViewDelegate(WordView& word_view);
  virtual ~SplittedWordViewDelegate();

  virtual void Layout() override;
  virtual void Paint(Canvas& canvas) override;

};


}  // le

#endif /* LE_SPLITTED_WORD_VIEW_DELEGATE_H_ */

#ifndef WORD_VIEW_H_
#define WORD_VIEW_H_

#include "view/view.h"
#include "view/word_view_delegate.h"
#include <memory>

namespace le {

class Word;

class WordView : public View
{
 public:
  WordView(Word& word);
  virtual ~WordView();

  virtual void Paint(Canvas& canvas) override;
  virtual void Layout() override;

  Word& GetWord() { return word_; }

  virtual View* GetNextParent() const override;
  
 private:
  Word& word_;
  std::unique_ptr<WordViewDelegate> delegate_;
};


}  // le

#endif /* WORD_VIEW_H_ */

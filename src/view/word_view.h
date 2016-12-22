#ifndef WORD_VIEW_H_
#define WORD_VIEW_H_

#include "view/view.h"

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

  
 private:
  Word& word_;
};


}  // le

#endif /* WORD_VIEW_H_ */

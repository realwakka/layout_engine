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

 private:
  Word& word_;
};


}  // le

#endif /* WORD_VIEW_H_ */

#ifndef WORD_VIEW_H_
#define WORD_VIEW_H_

namespace le {

class Word;

class WordView
{
 public:
  WordView(Word& word);
  virtual ~WordView();

 private:
  Word& word_;
};


}  // le

#endif /* WORD_VIEW_H_ */

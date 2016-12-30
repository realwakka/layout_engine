#ifndef LE_WORD_VIEW_DELEGATE_H_
#define LE_WORD_VIEW_DELEGATE_H_

namespace le {

class Canvas;
class WordView;

class WordViewDelegate
{
 public:
  WordViewDelegate(WordView& word_view) : word_view_(word_view) {}
  virtual void Layout() = 0;
  virtual void Paint(Canvas& canvas) = 0;

  WordView& GetWordView() { return word_view_; }

 private:
  WordView& word_view_;
};

}  // le


#endif /* LE_WORD_VIEW_DELEGATE_H_ */

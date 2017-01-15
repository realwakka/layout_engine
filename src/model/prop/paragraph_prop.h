#ifndef PARAGRAPH_PROP_H_
#define PARAGRAPH_PROP_H_

#include <memory>
#include "view/linebreaker/linebreaker.h"

namespace le {

class Indentation
{
 public:
  int GetStart() const { return start_; }
  int GetEnd() const { return end_; }
  int GetFirst() const { return first_; }
  int GetHanging() const { return hanging_; }

  int SetStart(int start) { start_ = start; }
  int SetEnd(int end) { end_ = end; }
  int SetFirst(int first) { first_ = first; }
  int SetHanging(int hanging) { hanging_ = hanging; }
  
 private:
  int start_;
  int end_;
  int first_;
  int hanging_;
};

class ParagraphProp
{
 public:
  ParagraphProp();
  virtual ~ParagraphProp();

  Indentation& GetIndentation() { return indentation_; }

  void SetLineBreaker(LineBreaker* linebreaker) { linebreaker_.reset(linebreaker); }
  LineBreaker* GetLineBreaker() { return linebreaker_.get(); }

 private:
  Indentation indentation_;
  std::unique_ptr<LineBreaker> linebreaker_;
  
};


}  // le

#endif /* PARAGRAPH_PROP_H_ */

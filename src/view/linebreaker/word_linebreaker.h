#ifndef LE_WORD_LINEBREAKER_H_
#define LE_WORD_LINEBREAKER_H_

#include "view/linebreaker/linebreaker.h"

namespace le {

class WordLineBreaker : public LineBreaker
{
 public:
  WordLineBreaker();
  virtual ~WordLineBreaker();
  
  void BreakLine(Paragraph& paragraph) override;
};

}  // le

#endif /* LE_WORD_LINEBREAKER_H_ */

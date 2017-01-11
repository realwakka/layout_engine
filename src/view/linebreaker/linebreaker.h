#ifndef LE_LINEBREAKER_H_
#define LE_LINEBREAKER_H_

namespace le {

class Paragraph;

class LineBreaker
{
 public:
  virtual void BreakLine(Paragraph& paragraph) = 0;
};


}  // le

#endif /* LE_LINEBREAKER_H_ */

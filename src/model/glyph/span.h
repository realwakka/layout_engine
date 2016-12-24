#ifndef LE_SPAN_H_
#define LE_SPAN_H_

namespace le {

class Span
{
 public:
  Span(int x, int y, int length, int coverage);
  virtual ~Span();

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetLength() const { return length_; }
  int GetCoverage() const { return coverage_; }

 private:
  int x_;
  int y_;
  int length_;
  int coverage_;
  
};


}  // le


#endif /* LE_SPAN_H_ */


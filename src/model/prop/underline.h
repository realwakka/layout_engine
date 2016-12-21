#ifndef UNDERLINE_H_
#define UNDERLINE_H_

namespace le {

enum class UnderlineType {
  kNone,
    kNormal,
    kWavy,
      };

class Underline
{
 public:
  Underline();
  virtual ~Underline();

 private:
  int count_;
  int color_;
  int thickness_;
  UnderlineType type_;

};


}  // le

#endif /* UNDERLINE_H_ */


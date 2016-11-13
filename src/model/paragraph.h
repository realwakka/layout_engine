#ifndef LE_PARAGRAPH_H_
#define LE_PARAGRAPH_H_

#include <vector>

#include "run.h"

namespace le {

class Paragraph
{
 public:
  Paragraph();
  virtual ~Paragraph();

  Run* getEnterRun() const { return &enter_; }
  
 private:
  std::vector<Run*> runs_;
  Run enter_;
};


}  // le

#endif /* LE_PARAGRAPH_H_ */

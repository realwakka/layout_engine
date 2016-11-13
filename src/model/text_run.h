#ifndef LE_TEXT_RUN_H_
#define LE_TEXT_RUN_H_

#include "run.h"

namespace le {

class TextRun : public Run
{
 public:
  TextRun();
  virtual ~TextRun();

  virtual void insertRun(Run* run) override;
  
};

}  // le

#endif /* LE_TEXT_RUN_H_ */


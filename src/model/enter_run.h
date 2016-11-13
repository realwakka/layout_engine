#ifndef LE_ENTER_RUN_H_
#define LE_ENTER_RUN_H_

#include "run.h"

namespace le {

class EnterRun : public Run
{
 public:
  EnterRun();
  virtual ~EnterRun();

  virtual void insertRun(Run* run) override;
};

}  // le

#endif /* LE_ENTER_RUN_H_ */


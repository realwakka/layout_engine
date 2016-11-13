#ifndef LE_ENTER_RUN_H_
#define LE_ENTER_RUN_H_

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


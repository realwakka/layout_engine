#ifndef LE_TEXT_RUN_H_
#define LE_TEXT_RUN_H_

#include "run.h"
#include <string>
#include <vector>
#include "type/container.h"

namespace le {

class Character;

class TextRun : public Run
{
 public:
  TextRun();
  virtual ~TextRun();

  //Run* Clone() override;

  Run* Split(Character* character) override;
  Run* Merge() override;


 private:
  int value_;

};

}  // le

#endif /* LE_TEXT_RUN_H_ */


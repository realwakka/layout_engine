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

};

}  // le

#endif /* LE_TEXT_RUN_H_ */


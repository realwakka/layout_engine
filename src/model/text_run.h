#ifndef LE_TEXT_RUN_H_
#define LE_TEXT_RUN_H_

#include "run.h"
#include <string>
#include <vector>

namespace le {

class Character;

class TextRun : public Run
{
 public:
  explicit TextRun(std::string text);
  explicit TextRun(Character* character);
  virtual ~TextRun();

  void setText(std::string text) { text_ = text; }

 private:
  std::string text_;
  std::vector<Character*> chars_;
  
  
};

}  // le

#endif /* LE_TEXT_RUN_H_ */


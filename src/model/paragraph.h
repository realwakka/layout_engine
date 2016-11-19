#ifndef LE_PARAGRAPH_H_
#define LE_PARAGRAPH_H_

#include <vector>
#include "enter_run.h"
#include "character.h"
#include "word.h"

namespace le {

class Paragraph
{
 public:
  Paragraph();
  virtual ~Paragraph();

  EnterRun* getEnterRun() { return &enter_; }
  void insertBefore(Run* run, Run* ref);
  
 private:
  std::vector<Run*> runs_;
  std::vector<Word*> words_;
  EnterRun enter_;

};


}  // le

#endif /* LE_PARAGRAPH_H_ */

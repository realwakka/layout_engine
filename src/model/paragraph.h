#ifndef LE_PARAGRAPH_H_
#define LE_PARAGRAPH_H_

#include <vector>
#include "enter_run.h"
#include "word.h"
#include "type/container.h"

namespace le {

class Paragraph
{
 public:
  Paragraph();
  virtual ~Paragraph();

  EnterRun* GetEnterRun() { return &enter_run_; }
  
  void InsertRun(Run* new_run, Run* ref_run) { runs_.InsertBefore(new_run, ref_run); }
  void InsertWord(Word* new_word, Word* ref_word) { words_.InsertBefore(new_word, ref_word); }

  Word* GetLastWord() { return words_.GetLastNode(); }
  Word* GetFirstWord() { return words_.GetFirstNode(); }
  
  Run* GetLastRun() { return runs_.GetLastNode(); }
  Run* GetFirstRun() { return runs_.GetFirstNode(); }
  

 private:
  Container<Run> runs_;
  Container<Word> words_;
  
  EnterRun enter_run_;
};


}  // le

#endif /* LE_PARAGRAPH_H_ */

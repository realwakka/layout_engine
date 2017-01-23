#ifndef LE_PARAGRAPH_H_
#define LE_PARAGRAPH_H_

#include <vector>
#include "enter_run.h"
#include "word.h"
#include "type/container.h"

#include "view/paragraph_view.h"
#include "model/prop/paragraph_prop.h"
#include "model/document.h"

namespace le {

class Paragraph
{
 public:
  Paragraph();
  virtual ~Paragraph();

  EnterRun* GetEnterRun() { return &enter_run_; }
  
  void InsertRun(Run* new_run, Run* ref_run);
  void RemoveRun(Run* run);
  void InsertWord(Word* new_word, Word* ref_word);
  void RemoveWord(Word* word);

  Word* GetLastWord() { return words_.GetLastNode(); }
  Word* GetFirstWord() { return words_.GetFirstNode(); }
  
  Run* GetLastRun() { return runs_.GetLastNode(); }
  Run* GetFirstRun() { return runs_.GetFirstNode(); }

  void PrintWord();
  void PrintRun();
  void PrintInfo();

  ParagraphView& GetView(){ return view_; }
  ParagraphProp& GetProp(){ return paragraph_prop_; }

  int GetIndex() { return child_.GetIndex(this); }
  Document* GetParent() const { return child_.GetParent(); }
  void SetParent(Document* parent) { child_.SetParent(parent); }
  Paragraph* GetNextSibling() { child_.GetNextSibling(this); }
  Paragraph* GetPrevSibling() { child_.GetPrevSibling(this); }
  

 private:
  Container<Run> runs_;
  Container<Word> words_;
  
  EnterRun enter_run_;
  ParagraphView view_;
  ParagraphProp paragraph_prop_;

  Child<Document, Paragraph> child_;
};


}  // le

#endif /* LE_PARAGRAPH_H_ */

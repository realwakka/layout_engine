#ifndef LE_RUN_H_
#define LE_RUN_H_

#include <memory>
#include "type/container.h"


namespace le {

class Paragraph;
class Character;
class Face;

class Run
{
 public:
  Run();
  virtual ~Run();
  
  void SetParagraph(Paragraph* paragraph) { run_.SetContainer(paragraph); }
  Paragraph* GetParagraph() { run_.GetContainer(); }

  std::list<Run*>::iterator GetIterator() { return run_.GetIterator(); }
  
 private:
  Paragraph* paragraph_;
  std::unique_ptr<Face> face_;

 private:
  Container<Character> chars_;
  Node<Paragraph, Run> run_;
};

}  // le

#endif /* LE_RUN_H_ */

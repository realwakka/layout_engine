#ifndef LE_RUN_H_
#define LE_RUN_H_

#include <memory>
#include "type/container.h"
#include "model/character/character.h"

namespace le {

class Paragraph;
class Character;
class Face;

class Run
{
 public:
  Run();
  virtual ~Run();
  
  void SetParagraph(Paragraph* paragraph) { node_.SetContainer(paragraph); }
  Paragraph* GetParagraph() { node_.GetContainer(); }

  Run* GetPrevRun();
  Run* GetNextRun();

  Character* GetLastCharacter() const { return chars_.GetLastNode(); }
  Character* GetFirstCharacter() const { return chars_.GetFirstNode(); }

  std::list<Run*>::iterator GetIterator() { return node_.GetIterator(); }
  void SetIterator(std::list<Run*>::iterator iter) { node_.SetIterator(iter); }

  void InsertCharacter(Character* character , Character* reference)
  {
    if( reference == nullptr ) 
      chars_.Append(character);
    else
      chars_.InsertBefore(character, reference->GetRunIterator());
  }
  
 private:
  Paragraph* paragraph_;
  std::unique_ptr<Face> face_;

 private:
  Container<Character> chars_;
  Node<Paragraph, Run> node_;
};

}  // le

#endif /* LE_RUN_H_ */

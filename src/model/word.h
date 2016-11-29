#ifndef LE_WORD_H_
#define LE_WORD_H_

#include "type/container.h"
#include <vector>

namespace le {

class Character;
class Paragraph;

class Word
{
 public:
  Word();
  virtual ~Word();

  void InsertBefore(Character* character, Character* reference);
  Word* GetPrevWord();

  Paragraph* GetParagraph() { return node_.GetContainer(); }
  void SetParagraph(Paragraph* paragraph) { node_.SetContainer(paragraph); }

  std::list<Word*>::iterator GetIterator() { return node_.GetIterator(); }

  void Split(Character* character);

 private:
  Container<Character> chars_;
  Node<Paragraph, Word> node_;
  
};


}  // le

#endif /* LE_WORD_H_ */

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

  void InsertCharacter(Character* character, Character* reference);
  void RemoveCharacter(Character* character);
  Word* GetPrevWord();
  Word* GetNextWord();

  Paragraph* GetParagraph() { return node_.GetContainer(); }
  void SetParagraph(Paragraph* paragraph) { node_.SetContainer(paragraph); }

  Character* GetLastCharacter() const { return chars_.GetLastNode(); }
  Character* GetFirstCharacter() const { return chars_.GetFirstNode(); }

  std::list<Word*>::iterator GetIterator() { return node_.GetIterator(); }
  void SetIterator(std::list<Word*>::iterator iter) { node_.SetIterator(iter); }

  void Split(Character* character);

 private:
  Container<Character> chars_;
  Node<Paragraph, Word> node_;
  
};


}  // le

#endif /* LE_WORD_H_ */

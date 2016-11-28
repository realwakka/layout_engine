#ifndef LE_WORD_H_
#define LE_WORD_H_

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

  Paragraph* GetParagraph() { return paragraph_; }
  void SetParagraph(Paragraph* paragraph) { paragraph_ = paragraph; }

 private:
  Paragraph* paragraph_;
  std::vector<Character*> chars_;
};


}  // le

#endif /* LE_WORD_H_ */

#ifndef LE_RUN_H_
#define LE_RUN_H_

namespace le {

class Paragraph;
class Character;

class Run
{
 public:
  void SetParagraph(Paragraph* paragraph) { paragraph_ = paragraph; }
  Paragraph* GetParagraph() { return paragraph_; }

  virtual void InsertBefore(Character* character, Character* reference) = 0;

 private:
  Paragraph* paragraph_;
};

}  // le

#endif /* LE_RUN_H_ */

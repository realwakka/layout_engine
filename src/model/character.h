#ifndef LE_CHARACTER_H_
#define LE_CHARACTER_H_

namespace le {

class CharacterView;
class Word;
class TextRun;

class Character
{
 public:
  Character(char c);
  virtual ~Character();

  char getChar() { return c_; }

  void SetTextRun(TextRun* run) { run_ = run; }
  TextRun* GetTextRun() { return run_; }

  void SetWord(Word* word) { word_ = word; }
  Word* GetWord() { return word_; }

  void InsertChar(Character* character);
    

 private:
  TextRun* run_;
  Word* word_;
  CharacterView* view_;
  char c_;
    
  
};


}  // le

#endif /* LE_CHARACTER_H_ */

#ifndef LE_CHARACTER_H_
#define LE_CHARACTER_H_

namespace le {

class CharacterView;
class TextRun;

class Character
{
 public:
  Character(char c);
  virtual ~Character();

  char getChar() { return c_; }

  void SetTextRun(TextRun* run) { run_ = run; }
  TextRun* GetTextRun() { return run_; }
    

 private:
  TextRun* run_;
  CharacterView* view_;
  char c_;
    
  
};


}  // le

#endif /* LE_CHARACTER_H_ */

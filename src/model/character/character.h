#ifndef LE_CHARACTER_H_
#define LE_CHARACTER_H_

namespace le {

class CharacterView;
class Word;
class Run;
class Glyph;

class Character
{
 public:
  Character(char c);
  virtual ~Character();

  char GetChar() { return c_; }

  void SetRun(Run* run) { run_ = run; }
  Run* GetRun() { return run_; }

  void SetWord(Word* word) { word_ = word; }
  Word* GetWord() { return word_; }

  virtual void InsertChar(Character* character);

  void SetGlyph(Glyph* glyph){ glyph_ = glyph; }
  Glyph* GetGlyph(){ return glyph_; }

 private:
  Run* run_;
  Word* word_;
  CharacterView* view_;
  Glyph* glyph_;
  char c_;
    
  
};


}  // le

#endif /* LE_CHARACTER_H_ */

#ifndef LE_CHARACTER_H_
#define LE_CHARACTER_H_

#include "type/container.h"
#include "model/glyph/glyph.h"
#include "view/character/character_view.h"
#include <memory>

namespace le {

Character* CreateCharacter(char ch);


class Word;
class Run;
class Face;
class Controller;
class Paragraph;

class Character
{
 public:
  Character(char c);
  virtual ~Character();

  char GetChar() const { return c_; }

  void SetRun(Run* run) { run_node_.SetContainer(run); }
  Run* GetRun() { return run_node_.GetContainer(); }

  void SetWord(Word* word) { word_node_.SetContainer(word); }
  Word* GetWord() { return word_node_.GetContainer(); }

  void SetGlyph(Glyph glyph){ glyph_ = glyph; }
  Glyph GetGlyph() const { return glyph_; }

  Character* GetPrevWordCharacter();
  Character* GetNextWordCharacter();
  std::list<Character*>::iterator GetWordIterator() { return word_node_.GetIterator(); }
  void SetWordIterator(std::list<Character*>::iterator iter) { word_node_.SetIterator(iter); }

  Character* GetPrevRunCharacter();
  Character* GetNextRunCharacter();
  std::list<Character*>::iterator GetRunIterator() { return run_node_.GetIterator(); }
  void SetRunIterator(std::list<Character*>::iterator iter) { run_node_.SetIterator(iter); }

  virtual Character* GetNextCharacter() = 0;
  virtual Character* GetPrevCharacter() = 0;

  virtual Character* GetNextParagraphCharacter() = 0;
  virtual Character* GetPrevParagraphCharacter() = 0;

  virtual Paragraph* GetParagraph() = 0;
  
  void UpdateGlyph();

  virtual CharacterView& GetView() = 0;
  virtual std::unique_ptr<Controller> GetController() {}

 private:
  Glyph glyph_;
  char c_;

  Node<Word, Character> word_node_;
  Node<Run, Character> run_node_;
};




}  // le

#endif /* LE_CHARACTER_H_ */

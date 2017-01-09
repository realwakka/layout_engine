#ifndef LE_RUN_H_
#define LE_RUN_H_

#include <memory>
#include "type/container.h"
#include "model/character/character.h"
#include "model/prop/run_prop.h"
#include "view/run/run_view.h"

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

  Run* GetPrevRun() const;
  Run* GetNextRun() const;

  Character* GetLastCharacter() const { return chars_.GetLastNode(); }
  Character* GetFirstCharacter() const { return chars_.GetFirstNode(); }

  std::list<Run*>::iterator GetIterator() { return node_.GetIterator(); }
  void SetIterator(std::list<Run*>::iterator iter) { node_.SetIterator(iter); }

  void InsertCharacter(Character* character , Character* reference);
  void RemoveCharacter(Character* character);
  void UpdateGlyph();

  RunProp& GetRunProp() { return run_prop_; }
  RunView& GetRunView() { return view_; }

  static Run* GetCachedRun() { return cached_run_; }
  static void SetCachedRun(Run* cached_run){ cached_run_ =  cached_run; }
  
 private:
  Paragraph* paragraph_;
  Face* face_;
  Container<Character> chars_;
  Node<Paragraph, Run> node_;
  RunProp run_prop_;
  RunView view_;

  static Run* cached_run_;
};

}  // le

#endif /* LE_RUN_H_ */

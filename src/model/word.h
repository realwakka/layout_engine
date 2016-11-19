#ifndef LE_WORD_H_
#define LE_WORD_H_

#include <vector>

namespace le {

class Character;

class Word
{
 public:
  Word();
  virtual ~Word();

  void InsertBefore(Character* character, Character* reference);

 private:
  std::vector<Character*> chars_;
};


}  // le

#endif /* LE_WORD_H_ */

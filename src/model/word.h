#ifndef LE_WORD_H_
#define LE_WORD_H_

#include <vector>

namespace le {

class Word
{
 public:
  Word();
  virtual ~Word();

 private:
  std::vector<Character*> chars_;
};


}  // le

#endif /* LE_WORD_H_ */

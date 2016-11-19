#include "word.h"

#include <algorithm>

namespace le {

Word::Word()
{}

Word::~Word()
{}

void Word::InsertBefore(Character* character, Character* reference)
{
  auto it = std::find(chars_.begin(), chars_.end(), reference);
  chars_.emplace(it, character);
  
}


}  // le

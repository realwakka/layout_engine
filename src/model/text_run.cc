#include "text_run.h"

#include <algorithm>

#include "model/paragraph.h"
#include "model/character/character.h"

namespace le {

TextRun::TextRun()
{
}

TextRun::~TextRun()
{

}

// Run* TextRun::Clone()
// {
//   return new TextRun(*this);
// }

Run* TextRun::Split(Character* character)
{
  if( character->GetRun() != this )
    throw std::exception();

  if( GetFirstCharacter() == character ) {
    return nullptr;
    
  } else {
    auto run = new TextRun();
    std::vector<Character*> removed;
    for( Character* ch = GetFirstCharacter() ;
         ch != character ; ch = ch->GetNextRunCharacter() ) {
      removed.push_back(ch);
    }

    for( Character* ch : removed ) {
      RemoveCharacter(ch);
      run->InsertCharacter(ch, nullptr);
    }

    GetParagraph()->InsertRun(run, this);

    return run;
  }
}

Run* TextRun::Merge() {
  auto prev = GetPrevRun();
  if( prev ) {
    std::vector<Character*> removed;
    for( auto ch = prev->GetFirstCharacter() ;
         ch ; ch = ch->GetNextRunCharacter() ) {
      removed.insert(removed.begin(), ch);
    }

    for( auto&& ch : removed ) {
      prev->RemoveCharacter(ch);
      InsertCharacter(ch, GetFirstCharacter());
    }

    GetParagraph()->RemoveRun(prev);
  }

  return prev;
}


}  // le

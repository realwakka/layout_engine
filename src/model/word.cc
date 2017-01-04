#include "word.h"

#include "model/character/character.h"
#include "model/character/space_character.h"
#include "model/paragraph.h"
#include "model/face/face_manager.h"
#include <algorithm>
#include <set>

namespace le {

Word::Word()
    : view_(*this)
{}

Word::~Word()
{}

void Word::InsertCharacter(Character* character, Character* reference)
{
  auto& characterview = character->GetView();
  
  if( reference == nullptr ) {
    auto it = chars_.Append(character);
    character->SetWordIterator(it);
    character->SetWord(this);

    View* wordview = nullptr;
    if( character->GetPrevWordCharacter() )
      wordview = character->GetPrevWordCharacter()->GetView().GetParent();
    else
      wordview = &GetView();

    wordview->AddChildAt(wordview->GetChildCount(), &characterview);
    
  } else  {
    auto it = chars_.InsertBefore(character, reference->GetWordIterator());
    character->SetWordIterator(it);
    character->SetWord(this);

    auto ref_view = reference->GetView();
    auto ref_index = ref_view.GetIndex();
    auto wordview = ref_view.GetParent();
    wordview->AddChildAt(ref_index, &characterview);
  }

  
}

void Word::RemoveCharacter(Character* character)
{
  chars_.Remove(character->GetWordIterator());
}

Word* Word::GetPrevWord()
{
  if( node_.GetContainer()->GetFirstWord() == this )
    return nullptr;
  else
    return *node_.GetPrev();
}

Word* Word::GetNextWord()
{
  if( node_.GetContainer()->GetLastWord() == this )
    return nullptr;
  else
    return *node_.GetNext();
}


void Word::Split(Character* character)
{
  if( character->GetWord() != this )
    throw std::exception();

  Word* word = new Word();
  std::vector<Character*> removed;
  for( Character* ch = GetFirstCharacter() ;
       ch != character ; ch = ch->GetNextWordCharacter() ) {
    removed.push_back(ch);
  }

  for( Character* ch : removed ) {
    RemoveCharacter(ch);
    word->InsertCharacter(ch, nullptr);
  }

  GetParagraph()->InsertWord(word, this);

  view_util::MoveChildsToNewParent(
      &character->GetView(),
      &word->GetView());
}

int Word::GetSpaceWidth() const
{
  auto width = 0;
  for( auto ch = GetLastCharacter() ; ch ; ch = ch->GetPrevWordCharacter() ) {
    if( typeid(*ch) == typeid(SpaceCharacter) ){
      width += ch->GetGlyph().GetAdvanceX();
    } else {
      break;
    }
  }
  
  return width;
}

int Word::GetWordWidth() const
{
  auto width = 0;
  for( Character* ch = GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() )
    width += ch->GetGlyph().GetAdvanceX();
  
  return width;
}

int Word::GetWordAscender() const
{
  std::set<Run*> runs;
  for( Character* ch = GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() )
    runs.emplace(ch->GetRun());

  auto ascender = 0;  
  for( Run* run : runs ) {
    auto prop = run->GetRunProp();
    auto face = FaceManager::GetInstance()->GetFace(prop);
    ascender = std::max(face.GetAscender(), ascender);
  }
  
  return ascender;
}

int Word::GetWordHeight() const
{
  std::set<Run*> runs;
  for( Character* ch = GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() )
    runs.emplace(ch->GetRun());

  auto height = 0;  
  for( Run* run : runs ) {
    auto prop = run->GetRunProp();
    auto face = FaceManager::GetInstance()->GetFace(prop);
    height = std::max(face.GetHeight(), height);
  }
  return height;
}


}  // le

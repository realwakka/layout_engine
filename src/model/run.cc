#include "run.h"

#include "model/face/face.h"
#include "model/face/face_manager.h"
#include "model/paragraph.h"

namespace le {

Run* Run::cached_run_ = nullptr;

Run::Run()
    // : view_(*this)
{
  face_ = new Face();
  //face_ = FaceManager::GetInstance()->GetDefaultFace();
}

Run::~Run()
{}

Run* Run::GetPrevRun() const
{
  if( node_.GetContainer()->GetFirstRun() == this )
    return nullptr;
  else
    return *node_.GetPrev();
}

Run* Run::GetNextRun() const
{
  if( node_.GetContainer()->GetLastRun() == this )
    return nullptr;
  else
    return *node_.GetNext();
}


void Run::InsertCharacter(Character* character, Character* reference)
{
  if( reference == nullptr ) {
    auto it = chars_.Append(character);
    character->SetRunIterator(it);
    character->SetRun(this);
    
  } else {
    auto it = chars_.InsertBefore(character, reference->GetRunIterator());
    character->SetRunIterator(it);
    character->SetRun(this);
  }

  character->UpdateGlyph();
}

void Run::RemoveCharacter(Character* character)
{
  chars_.Remove(character->GetRunIterator());
}


void Run::UpdateGlyph()
{
  for( Character* character = GetFirstCharacter() ; character ; character = character->GetNextRunCharacter() ) {
    character->UpdateGlyph();
  }
}

Run* Run::Split(Character* character)
{
  if( character->GetRun() != this )
    throw std::exception();

  if( GetFirstCharacter() == character ) {
    return nullptr;
    
  } else {
    Run* run = new Run();
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

Run* Run::Merge() {
  auto prev = GetPrevRun();
  if( prev ) {
    std::vector<Character*> removed;
    for( auto ch = prev->GetFirstCharacter() ;
         ch ; ch = ch->GetNextRunCharacter() ) {
      removed.push_back(ch);
    }

    for( auto&& ch : removed ) {
      prev->RemoveCharacter(ch);
      InsertCharacter(ch, GetFirstCharacter());
    }
  }

  return prev;
}

}  // le

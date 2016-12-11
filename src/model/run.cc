#include "run.h"

#include "model/face/face.h"
#include "model/face/face_manager.h"
#include "model/paragraph.h"

namespace le {

Run::Run()
{
  face_ = new Face("NanumGothicOTF", 10);
  //face_ = FaceManager::GetInstance()->GetDefaultFace();
}

Run::~Run()
{
  
}


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
  } else  {
    auto it = chars_.InsertBefore(character, reference->GetRunIterator());
    character->SetRunIterator(it);
    character->SetRun(this);
  }

  character->UpdateGlyph(*face_);
}

void Run::UpdateGlyph()
{
  for( Character* character = GetFirstCharacter() ; character ; character = character->GetNextRunCharacter() ) {
    character->UpdateGlyph(*face_);
  }
}


}  // le

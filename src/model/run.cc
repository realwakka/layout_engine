#include "run.h"

#include "model/face/face.h"
#include "model/face/face_manager.h"
#include "model/paragraph.h"

namespace le {

Run* Run::cached_run_ = nullptr;

Run::Run()
    : view_(*this)
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
  auto& characterview = character->GetView();
  
  if( reference == nullptr ) {
    auto it = chars_.Append(character);
    character->SetRunIterator(it);
    character->SetRun(this);

    View* runview = nullptr;
    if(GetLastCharacter()) 
      runview = GetLastCharacter()->GetView().GetParent();
    else
      runview = &GetRunView();
    
    runview->AddChildAt(runview->GetChildCount(), &characterview);
    
  } else  {
    auto it = chars_.InsertBefore(character, reference->GetRunIterator());
    character->SetRunIterator(it);
    character->SetRun(this);

    auto ref_view = reference->GetView();
    auto ref_index = ref_view.GetIndex();
    auto runview = ref_view.GetParent();
    runview->AddChildAt(ref_index, &characterview);

  }

  character->UpdateGlyph();
}

void Run::RemoveCharacter(Character* character)
{
  auto view_index = character->GetView().GetIndex();
  character->GetView().GetParent()->RemoveChildAt(view_index);
  
  chars_.Remove(character->GetRunIterator());
}


void Run::UpdateGlyph()
{
  for( Character* character = GetFirstCharacter() ; character ; character = character->GetNextRunCharacter() ) {
    character->UpdateGlyph();
  }
}


}  // le

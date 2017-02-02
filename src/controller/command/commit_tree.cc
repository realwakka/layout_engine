#include "commit_tree.h"

#include "controller/command/commit.h"
#include "controller/command/command.h"

namespace le {

CommitTree* CommitTree::instance_ = nullptr;

CommitTree::CommitTree()
    : current_(new Commit())
{}
CommitTree::~CommitTree()
{}

bool CommitTree::DoCommit()
{
  current_->SetComplete(true);
}

void CommitTree::AddCommand(Command* command)
{
  if( current_ == nullptr ) {
    current_ = new Commit();
  } else {
    auto now = std::time(nullptr);
    auto diff = now - current_->GetTime();
    if( diff > 5 )
      DoCommit();
    
    if( current_->GetComplete() ) {
      auto commit = new Commit();
      current_->AppendChild(commit);
      current_ = commit;
    }
  }

  command->Apply();
  current_->AddCommand(command);
}

CommitTree* CommitTree::GetInstance()
{
  if( instance_ == nullptr )
    instance_ = new CommitTree();
  
  return instance_;
}

void CommitTree::UnDo()
{
  if( current_ ) {
    DoCommit();
    current_->UnApply();
    current_ = current_->GetParent();
  }
}
void CommitTree::ReDo()
{
  if( current_ && current_->GetLastChild() ) {
    DoCommit();
    current_ = current_->GetLastChild();
    current_->ReApply();
  }
}



}  // le

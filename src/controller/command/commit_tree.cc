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
  if( current_->GetChildCount() != 0 ) {
    auto commit = new Commit();
    current_->AppendChild(commit);
    current_ = commit;
  }
}

void CommitTree::AddCommand(Command* command)
{
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
  DoCommit();
  if( current_->GetParent() ) {
    current_->GetParent()->UnApply();
    current_ = current_->GetParent();
  }
  
}
void CommitTree::ReDo()
{
  DoCommit();
}



}  // le

#include "commit_tree.h"

#include "controller/command/commit.h"

namespace le {

CommitTree* CommitTree::instance_ = nullptr;

CommitTree::CommitTree()
    : current_(new Commit())
{}
CommitTree::~CommitTree()
{}

bool CommitTree::DoCommit()
{
  
}

void CommitTree::AddCommand(Command* command)
{}

CommitTree* CommitTree::GetInstance()
{
  if( instance_ == nullptr )
    instance_ = new CommitTree();
  
  return instance_;
}


}  // le

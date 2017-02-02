#include "commit.h"

#include "controller/command/command.h"

namespace le {

Commit::Commit()
    : complete_(false),
      time_(std::time(nullptr))
{}

Commit::~Commit()
{}

void Commit::UnApply()
{
  for( auto it = commands_.rbegin() ; it != commands_.rend() ; ++it ) {
    (*it)->UnApply();
  }
}

void Commit::ReApply()
{
  for( Command* command : commands_ ) {
    command->ReApply();
  }
}


}  // le

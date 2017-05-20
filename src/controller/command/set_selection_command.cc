#include "set_selection_command.h"

#include "render_text.h"

namespace le {


SetSelectionCommand::SetSelectionCommand(RenderText* rendertext, std::shared_ptr<Controller> new_selection, std::shared_ptr<Controller> old_selection)
    : rendertext_(rendertext),
      new_selection_(new_selection),
      old_selection_(old_selection)
{}

SetSelectionCommand::SetSelectionCommand(RenderText* rendertext, std::shared_ptr<Controller> new_selection)
    : rendertext_(rendertext),
      new_selection_(new_selection),
      old_selection_(rendertext->GetController())
{}


SetSelectionCommand::~SetSelectionCommand()
{}

void SetSelectionCommand::Apply()
{
  rendertext_->SetController(new_selection_);
}
void SetSelectionCommand::UnApply()
{
  rendertext_->SetController(old_selection_);
}
void SetSelectionCommand::ReApply()
{
  rendertext_->SetController(new_selection_);
}


}  // le

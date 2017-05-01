#include "set_selection_command.h"

#include "render_text.h"

namespace le {


SetSelectionCommand::SetSelectionCommand(RenderText* rendertext, std::shared_ptr<Selection> new_selection, std::shared_ptr<Selection> old_selection)
    : rendertext_(rendertext),
      new_selection_(new_selection),
      old_selection_(old_selection)
{}

SetSelectionCommand::~SetSelectionCommand()
{}

void SetSelectionCommand::Apply()
{
  rendertext_->SetSelection(new_selection_);
}
void SetSelectionCommand::UnApply()
{
  rendertext_->SetSelection(old_selection_);
}
void SetSelectionCommand::ReApply()
{
  rendertext_->SetSelection(new_selection_);
}


}  // le

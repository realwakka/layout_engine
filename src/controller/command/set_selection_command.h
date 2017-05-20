#ifndef LE_SET_SELECTION_COMMAND_H_
#define LE_SET_SELECTION_COMMAND_H_

#include <memory>
#include "controller/command/command.h"
#include "controller/controller.h"

namespace le {

class Selection;
class RenderText;

class SetSelectionCommand : public Command
{
 public:
  SetSelectionCommand(RenderText* rendertext, std::shared_ptr<Controller> new_selection, std::shared_ptr<Controller> old_selection);
  SetSelectionCommand(RenderText* rendertext, std::shared_ptr<Controller> new_selection);
  virtual ~SetSelectionCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "Set Selection"; }

 private:
  RenderText* rendertext_;
  std::shared_ptr<Controller> old_selection_;
  std::shared_ptr<Controller> new_selection_;
  
  
};

}  // le

#endif /* LE_SET_SELECTION_COMMAND_H_ */

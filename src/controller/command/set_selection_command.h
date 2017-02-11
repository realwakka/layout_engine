#ifndef LE_SET_SELECTION_COMMAND_H_
#define LE_SET_SELECTION_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Selection;
class RenderText;

class SetSelectionCommand : public Command
{
 public:
  SetSelectionCommand(RenderText* rendertext, Selection* new_selection, Selection* old_selection);
  virtual ~SetSelectionCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "Set Selection"; }

 private:
  Selection* old_selection_;
  Selection* new_selection_;
  RenderText* rendertext_;
  
};


}  // le

#endif /* LE_SET_SELECTION_COMMAND_H_ */

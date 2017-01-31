#ifndef LE_INITIAL_COMMAND_H_
#define LE_INITIAL_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class InitialCommand : public Command
{
 public:
  InitialCommand();
  virtual ~InitialCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "Initial Command"; }
  
};


}  // le

#endif /* LE_INITIAL_COMMAND_H_ */

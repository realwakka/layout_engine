#ifndef LE_SPLIT_RUN_COMMAND_H_
#define LE_SPLIT_RUN_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Character;
class Run;

class SplitRunCommand : public Command
{
 public:
  SplitRunCommand(Character* character);
  virtual ~SplitRunCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "SplitRun"; }

 private:
  Character* character_;
  Run* inserted_run_;
  
};


}  // le

#endif /* LE_SPLIT_RUN_COMMAND_H_ */

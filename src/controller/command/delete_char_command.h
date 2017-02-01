#ifndef LE_DELETE_CHAR_COMMAND_H_
#define LE_DELETE_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class DeleteCharCommand : public Command
{
 public:
  DeleteCharCommand();
  virtual ~DeleteCharCommand();

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { "Modify Char"; }
  
};


}  // le

#endif /* LE_DELETE_CHAR_COMMAND_H_ */

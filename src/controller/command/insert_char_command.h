#ifndef LE_INSERT_CHAR_COMMAND_H_
#define LE_INSERT_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class InsertCharCommand : public Command
{
 public:
  InsertCharCommand();
  virtual ~InsertCharCommand();

  void Apply() override;
  void UnApply() override;
  std::string GetDecription() override;
  

};


}  // le


#endif /* LE_INSERT_CHAR_COMMAND_H_ */

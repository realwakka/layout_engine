#ifndef LE_INSERT_CHAR_COMMAND_H_
#define LE_INSERT_CHAR_COMMAND_H_

#include "controller/command/command.h"

namespace le {

class Paragraph;
class Character;
class CharCommandDelegate;

class InsertCharCommand : public Command
{
 public:
  InsertCharCommand(Paragraph* paragraph, Character* character, Character* inserted);

  virtual ~InsertCharCommand();

  void AppendChild(Command* child) override;

  void Apply() override;
  void UnApply() override;
  void ReApply() override;
  std::string GetDecription() override { return "Insert Char"; }

 private:
  bool MergeAvailable(Command* child) const;

 private:
  std::vector<CharCommandDelegate*> delegate_list_;
  
  //selected
  Paragraph* paragraph_;
  Character* character_;

};


}  // le


#endif /* LE_INSERT_CHAR_COMMAND_H_ */

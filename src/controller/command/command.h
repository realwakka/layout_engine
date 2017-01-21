#ifndef LE_COMMAND_H_
#define LE_COMMAND_H_

#include "type/container.h"
#include <string>

namespace le {

class Command
{
 public:
  virtual void Apply() = 0;
  virtual void UnApply() = 0;

  virtual std::string GetDecription() = 0;

  Command* GetFirstChild() { return parent_.GetFirstChild(); }
  Command* GetLastChild() { return parent_.GetLastChild(); }
  Command* GetChildAt(int index) const { return parent_.GetChildAt(index); }
  int GetChildCount() const { return parent_.GetChildCount(); }
  void AddChildAt(int index, Command* child) { parent_.AddChildAt(index, child, this); }
  void AppendChild(Command* child) { parent_.AppendChild(child, this); }

  int GetIndex() { return child_.GetIndex(this); }
  Command* GetParent() const { return child_.GetParent(); }
  void SetParent(Command* parent) { child_.SetParent(parent); }
  Command* GetNextSibling() { child_.GetNextSibling(this); }
  Command* GetPrevSibling() { child_.GetPrevSibling(this); }

 private:
  Parent<Command, Command> parent_;
  Child<Command, Command> child_;
};


}  // le

#endif /* LE_COMMAND_H_ */

#ifndef LE_COMMIT_H_
#define LE_COMMIT_H_

#include "type/container.h"
#include <vector>
#include <ctime>

namespace le {

class Command;

class Commit
{
 public:
  Commit();
  virtual ~Commit();

  void UnApply();
  void ReApply();

  void AddCommand(Command* command) { commands_.push_back(command); }
  int GetCommandCount() const { return commands_.size(); }

  void AppendChild(Commit* child) { parent_.AppendChild(child, this); }

  Commit* GetFirstChild() { return parent_.GetFirstChild(); }
  Commit* GetLastChild() { return parent_.GetLastChild(); }
  Commit* GetChildAt(int index) const { return parent_.GetChildAt(index); }
  int GetChildCount() const { return parent_.GetChildCount(); }
  void AddChildAt(int index, Commit* child) { parent_.AddChildAt(index, child, this); }

  int GetIndex() { return child_.GetIndex(this); }
  Commit* GetParent() const { return child_.GetParent(); }
  void SetParent(Commit* parent) { child_.SetParent(parent); }
  Commit* GetNextSibling() { child_.GetNextSibling(this); }
  Commit* GetPrevSibling() { child_.GetPrevSibling(this); }

  bool GetComplete() const { return complete_; }
  void SetComplete( bool complete ) { complete_ = complete; }

  std::time_t GetTime() const { return time_; }

 private:
  Parent<Commit, Commit> parent_;
  Child<Commit, Commit> child_;
  std::vector<Command*> commands_;
  bool complete_;
  std::time_t time_;
  
};


}  // le

#endif /* LE_COMMIT_H_ */

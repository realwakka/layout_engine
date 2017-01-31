#ifndef LE_COMMIT_TREE_H_
#define LE_COMMIT_TREE_H_

namespace le {

class Command;
class Commit;

class CommitTree
{
 public:
  CommitTree();
  virtual ~CommitTree();

  bool DoCommit();
  void AddCommand(Command* command);

  static CommitTree* GetInstance();

 private:
  Commit* current_;

 private:
  static CommitTree* instance_;
  
};


}  // le

#endif /* LE_COMMIT_TREE_H_ */

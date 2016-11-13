#ifndef LE_RUN_VIEW_H_
#define LE_RUN_VIEW_H_

namespace le {

class RunView
{
 public:
  RunView(Run& run);
  virtual ~RunView();

 public:
  Run& run_;
};


}  // le

#endif /* LE_RUN_VIEW_H_ */

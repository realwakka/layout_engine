#ifndef LE_LINE_VIEW_H_
#define LE_LINE_VIEW_H_

namespace le {

class LineView
{
 public:
  LineView();
  virtual ~LineView();

 private:
  std::vector<RunView> run_views_;

};


}  // le

#endif /* LE_LINE_VIEW_H_ */

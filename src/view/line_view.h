#ifndef LE_LINE_VIEW_H_
#define LE_LINE_VIEW_H_

#include <vector>

namespace le {

class WordView;

class LineView
{
 public:
  LineView();
  virtual ~LineView();

 private:
  std::vector<WordView*> word_views_;

};


}  // le

#endif /* LE_LINE_VIEW_H_ */

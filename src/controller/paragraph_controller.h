#ifndef LE_PARAGRAPH_CONTROLLER_H_
#define LE_PARAGRAPH_CONTROLLER_H_

#include <string>

namespace le {


class Selection
{
 public:
  
};

class Paragraph;
class Run;

class ParagraphController
{
 public:
  ParagraphController();
  virtual ~ParagraphController();

  void insertText(std::string text);

 private:
  Paragraph* paragraph_;
  Run* selected_run_;
  int selected_index_;
  
};



}  // le

#endif /* LE_PARAGRAPH_CONTROLLER_H_ */

#ifndef LE_PARAGRAPH_CONTROLLER_H_
#define LE_PARAGRAPH_CONTROLLER_H_

#include <string>

namespace le {

class Paragraph;
class Run;
class Character;

class ParagraphController
{
 public:
  ParagraphController();
  virtual ~ParagraphController();

  void insertText(std::string text);

 private:
    Character* selected_;
    
  Paragraph* paragraph_;
  Run* selected_run_;
  int selected_index_;
  
};



}  // le

#endif /* LE_PARAGRAPH_CONTROLLER_H_ */

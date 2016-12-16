#ifndef LE_PARAGRAPH_CONTROLLER_H_
#define LE_PARAGRAPH_CONTROLLER_H_

#include <string>
#include "model/paragraph.h"

namespace le {

class Paragraph;
class Run;
class Character;

class ParagraphController
{
 public:
  ParagraphController();
  virtual ~ParagraphController();

  void InsertText(std::string text);
  void Layout();
  Paragraph& GetParagraph() { return paragraph_; }

 private:
  Paragraph paragraph_;
  Character* selected_char_;
  int selected_index_;
  
};



}  // le

#endif /* LE_PARAGRAPH_CONTROLLER_H_ */

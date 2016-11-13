#ifndef LE_RUN_H_
#define LE_RUN_H_

namespace le {

class Paragraph;

class Run
{
 public:
  virtual void insertRun(Run* run) = 0;
  
  void setParagraph(Paragraph* paragraph) { paragraph_ = paragraph; }
  Paragraph* getParagraph() { return paragraph_; }

 private:
  Paragraph* paragraph_;
};

}  // le

#endif /* LE_RUN_H_ */

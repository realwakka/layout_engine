#ifndef RUNPROP_H_
#define RUNPROP_H_

#include "model/face/face.h"
#include "model/prop/font.h"

namespace le {

class RunProp
{
 public:
  RunProp();
  virtual ~RunProp();

  int GetSize() const { return size_; }
  void SetSize(int size) { size_ = size; }



 private:
  int size_;
  Font font_;
  
};


}  // le

#endif /* RUNPROP_H_ */

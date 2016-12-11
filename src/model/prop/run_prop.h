#ifndef RUNPROP_H_
#define RUNPROP_H_

#include "model/face/face.h"

namespace le {

class RunProp
{
 public:
  RunProp();
  virtual ~RunProp();

  int GetSize() const { return size_; }
  void SetSize(int size) { size_ = size; }

  Face GetFace() const { return face_; }
  void SetFace(Face face) { face_ = face; }

 private:
  int size_;
  Face face_;
  
};


}  // le

#endif /* RUNPROP_H_ */

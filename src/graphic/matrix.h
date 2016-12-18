#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>

namespace le {

enum {
  kMScaleX,
  kMSkewX,
  kMTransX,
  kMSkewY,
  kMScaleY,
  kMTransY,
  kMPersp0,
  kMPersp1,
  kMPersp2
};

class Matrix
{
 public:
  Matrix();
  Matrix( const Matrix& matrix);
  virtual ~Matrix();
  
  float GetScaleX() const { return mat_[kMScaleX]; }
  float GetScaleY() const { return mat_[kMScaleY]; }
  float GetSkewY() const { return mat_[kMSkewY]; }
  float GetSkewX() const { return mat_[kMSkewX]; }
  float GetTranslateX() const { return mat_[kMTransX]; }
  float GetTranslateY() const { return mat_[kMTransY]; }
  float GetPerspX() const { return mat_[kMPersp0]; }
  float GetPerspY() const { return mat_[kMPersp1]; }

  void SetScaleX(float v) { this->Set(kMScaleX, v); }
  void SetScaleY(float v) { this->Set(kMScaleY, v); }
  void SetSkewY(float v) { this->Set(kMSkewY, v); }
  void SetSkewX(float v) { this->Set(kMSkewX, v); }
  void SetTranslateX(float v) { this->Set(kMTransX, v); }
  void SetTranslateY(float v) { this->Set(kMTransY, v); }
  void SetPerspX(float v) { this->Set(kMPersp0, v); }
  void SetPerspY(float v) { this->Set(kMPersp1, v); }

  void Set(int index, float value) { mat_[index] = value; }
  float Get(int index) const { return mat_[index]; }

  void SetTranslate(float x, float y);
  void Translate(float x, float y);
  void Reset();

  std::array<float, 3> Concat(const std::array<float, 3>& input) const;
  Matrix Concat(const Matrix& matrix) const;  

 public:
  float mat_[9];
};


}  // le

#endif /* MATRIX_H_ */

#include "matrix.h"

namespace le {

Matrix::Matrix()
{
  Reset();
}
Matrix::~Matrix()
{}

void Matrix::SetTranslate(float dx, float dy) {
  if (dx || dy) {
    mat_[kMTransX] = dx;
    mat_[kMTransY] = dy;

    mat_[kMScaleX] = mat_[kMScaleY] = mat_[kMPersp2] = 1;
    mat_[kMSkewX]  = mat_[kMSkewY] =
    mat_[kMPersp0] = mat_[kMPersp1] = 0;
  } 
}

void Matrix::Reset()
{
  mat_[kMScaleX] = mat_[kMScaleY] = mat_[kMPersp2] = 1;
  mat_[kMSkewX]  = mat_[kMSkewY] =
  mat_[kMTransX] = mat_[kMTransY] =
  mat_[kMPersp0] = mat_[kMPersp1] = 0;
}

}  // le

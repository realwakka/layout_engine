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

std::array<float, 3> Matrix::Concat(const std::array<float, 3>& input) const
{
  std::array<float, 3> result;
  for( int i=0 ; i < 3 ; ++i ) {
    float tmp = 0;
    for( int j=0 ; j < 3 ; ++j ) {
      tmp += mat_[ i * 3 + j ] + input[j];
    }
    result[i] = tmp;
  }
  return result;
}

Matrix Matrix::Concat(const Matrix& matrix) const
{
  Matrix result;
  for( int i=0 ; i<3 ; ++i ) {
    for( int j=0 ; j<3 ; ++j ) {
      float tmp = 0;
      for( int k=0 ; k<3 ; ++k ) {
        tmp += Get(i * 3 + k) * matrix.Get( k * 3 + j);
      }
      result.Set(i*3+j, tmp);
    }
  }
  return result;
}

}  // le

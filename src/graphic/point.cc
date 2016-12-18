#include "point.h"

#include "graphic/matrix.h"
#include <array>

namespace le {


Point::Point()
    : Point(0, 0)
{}

Point::Point(int x, int y)
    : x_(x),
      y_(y)
{}

Point::~Point()
{}

Point Point::Transform(const Matrix& matrix) const
{
  Point result;
  std::array<float, 3> input = {(float)x_, (float)y_, 1.0f};
  auto array = matrix.Concat(input);
  result.SetX(array[0]);
  result.SetY(array[1]);
  return result;
}

}  // le

#include "point.h"

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

}  // le

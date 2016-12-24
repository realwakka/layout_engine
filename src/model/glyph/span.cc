#include "span.h"

namespace le {

Span::Span(int x, int y, int length, int coverage)
    : x_(x),
      y_(y),
      length_(length),
      coverage_(coverage)
{}
  
Span::~Span()
{}

}  // le

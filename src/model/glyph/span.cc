#include "span.h"

namespace le {

Span::Span(int x, int y, int length)
    : x_(x),
      y_(y),
      length_(length)
{}
  
Span::~Span()
{}

}  // le

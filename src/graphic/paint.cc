#include "paint.h"

namespace le {

Paint::Paint()
    : color_(kColorBlack),
      stroke_width_(1),
      style_(Style::kFill)
{

}

Paint::~Paint()
{

}


}  // le

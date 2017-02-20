#include "run_prop.h"
#include "model/prop/underline/single_underline.h"

namespace le {

RunProp::RunProp()
    : size_(10),
      color_(kColorBlack),
      italic_(false),
      bold_(false),
      m_underline(new SingleUnderline())
{}

RunProp::~RunProp()
{}

}  // le

#include "section_prop.h"

namespace le {

PageMargin::PageMargin()
    : top_(1440),
      right_(1440),
      bottom_(1440),
      left_(1440),
      header_(720),
      footer_(720),
      gutter_(0)
{}

PageMargin::~PageMargin()
{}

PageSize::PageSize()
    : width_(12240),
      height_(15840)
{}

PageSize::~PageSize()
{}


SectionProp::SectionProp()
{}

SectionProp::~SectionProp()
{}


}  // le

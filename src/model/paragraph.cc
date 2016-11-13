#include "paragraph.h"

#include <algorithm>

namespace le {

Paragraph::Paragraph()
{}

Paragraph::~Paragraph()
{}

void Paragraph::insertBefore(Run* run, Run* ref)
{
  auto it = std::find(runs_.begin(), runs_.end(), ref);
  if( it == runs_.end() ) {
    runs_.emplace( it, run );
  }
}

}  // le

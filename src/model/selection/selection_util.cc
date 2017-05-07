#include "model/selection/selection_util.h"

#include "model/selection/caret_selection.h"
#include "model/selection/block_selection.h"

namespace le {
namespace selection_util {

std::shared_ptr<Selection> createTextSelection(Character* start, Character* end, CaretPosition pos)
{
  if( start == end ) {
    return std::make_shared<CaretSelection>(*start);
  } else {
    return std::make_shared<BlockSelection>(*start, *end, pos);
  }
}

}  // selection_util
}  // le

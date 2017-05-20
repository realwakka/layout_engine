#include "model/selection/selection_util.h"

#include "model/selection/caret_selection.h"
#include "model/selection/block_selection.h"

#include "controller/caret_controller.h"
#include "controller/block_selection_controller.h"


namespace le {
namespace selection_util {

std::shared_ptr<Controller> createTextSelection(RenderText* rendertext, Character* start, Character* end, CaretPosition pos)
{
  if( start == end ) {
    return std::make_shared<CaretController>(*start, rendertext);
  } else {
    return std::make_shared<BlockSelectionController>(*rendertext, *start, *end, pos);
  }
}

}  // selection_util
}  // le

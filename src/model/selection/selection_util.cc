#include "model/selection/selection_util.h"

#include "model/character/character.h"

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


std::shared_ptr<Controller> createSelection(RenderText* rendertext, Character* src, Character* dst)
{
  if( src == dst ) {
    return std::make_shared<CaretController>(*src, rendertext);
  } else {
    if( character_util::GetOrderedCharacter(src, dst) ) {
      return std::make_shared<BlockSelectionController>(*rendertext, *src, *dst, CaretPosition::kStart);
    } else {
      return std::make_shared<BlockSelectionController>(*rendertext, *dst, *src, CaretPosition::kEnd);
    }

  }
}

}  // selection_util
}  // le

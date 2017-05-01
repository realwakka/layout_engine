#include "model/selection/block_selection.h"

#include "controller/block_selection_controller.h"

namespace le {

BlockSelection::BlockSelection(Character& start, Character& end)
    : start_(start),
      end_(end)
{

}
BlockSelection::~BlockSelection()
{

}

std::unique_ptr<Controller> BlockSelection::GetController(RenderText* rendertext) const
{
  return std::unique_ptr<Controller>(new BlockSelectionController(*rendertext, start_, end_));
}

View& BlockSelection::GetView()
{
  return view_;
}


}  // le

#include "model/selection/block_selection.h"

#include "controller/block_selection_controller.h"

namespace le {

BlockSelection::BlockSelection(Character& start, Character& end, CaretPosition pos)
    : start_(start),
      end_(end),
      pos_(pos),
      view_(*this)
{

}
BlockSelection::~BlockSelection()
{

}

std::unique_ptr<Controller> BlockSelection::GetController(RenderText* rendertext) const
{
  return std::unique_ptr<Controller>(new BlockSelectionController(*rendertext, *this));
}

View& BlockSelection::GetView()
{
  return view_;
}

Character* BlockSelection::GetCaret() const
{
  if( pos_ == CaretPosition::kStart )
    return &start_;
  else
    return &end_;
}

}  // le

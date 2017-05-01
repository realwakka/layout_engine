#include "controller/block_selection_controller.h"

namespace le {

BlockSelectionController::BlockSelectionController(RenderText& rendertext, Character& start, Character& end)
    : rendertext_(rendertext),
      start_(start),
      end_(end)
{
}

BlockSelectionController::~BlockSelectionController()
{
}

void BlockSelectionController::InsertText(std::string text)
{
}

void BlockSelectionController::BackSpaceChar()
{
}

void BlockSelectionController::SetBold(bool bold) 
{
}

void BlockSelectionController::SetItalic(bool italic) 
{
}

void BlockSelectionController::SetSize(int size) 
{
}

void BlockSelectionController::InsertChar(Character* character)
{
}
void BlockSelectionController::SetPageSize(int width, int height)
{
}
  
void BlockSelectionController::OnMousePressed(const MouseEvent& event)
{

}

void BlockSelectionController::OnKeyDown(const KeyEvent& event)
{
  
}


}  // le



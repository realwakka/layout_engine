#include "controller/block_selection_controller.h"

namespace le {

BlockSelectionController::BlockSelectionController(RenderText& rendertext, Character& start, Character& end)
    : rendertext_(rendertext),
      start_(start),
      end_(end),
      reversed_(false)
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
  // if( event.GetShiftDown() ) {
  //   if( event.GetCode() == KeyboardCode::VKEY_RIGHT ) {
  //     auto next = enter_char_.GetNextCharacter();
  //     if( next ) {
  //       auto command = new SetSelectionCommand(
  //           rendertext_,
  //           std::make_shared<BlockSelection>(enter_char_, *next, false),
  //           rendertext_->GetSelection() );

  //       rendertext_->GetCommitTree()->AddCommand(command);
  //     }

  //   } else if( event.GetCode() == KeyboardCode::VKEY_LEFT ) {
  //     auto prev = enter_char_.GetPrevCharacter();
  //     if( prev ) {
  //       auto next_sel = new BlockSelection(*prev, enter_char_, false);
  //       auto command = new SetSelectionCommand(
  //           rendertext_,
  //           std::make_shared<BlockSelection>(*prev, enter_char_, false),
  //           rendertext_->GetSelection() );

  //       rendertext_->GetCommitTree()->AddCommand(command);
  //     }
  //   }

    
  // }
}

}  // le



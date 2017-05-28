#include "controller/block_selection_controller.h"

#include "render_text.h"

#include "model/selection/block_selection.h"
#include "model/character/character.h"
#include "model/selection/selection_util.h"

#include "view/line_view.h"

#include "controller/event/key_event.h"
#include "controller/command/set_selection_command.h"
#include "controller/command/insert_char_command.h"
#include "controller/command/delete_char_command.h"
#include "controller/command/delete_text_command.h"
#include "controller/command/run_prop/set_run_prop_command.h"

namespace le {

namespace {

template<typename Setter, typename Getter, typename Value>
void SetRunProp(RenderText& rendertext, const BlockSelection& selection, Setter setter,Getter getter, Value value){
  rendertext.Commit();
  
  auto begin = selection.GetStart();
  auto end = selection.GetEnd();
  auto command = command_util::CreateSetRunPropCommand(begin, end, setter, getter, value);

  rendertext.GetCommitTree()->AddCommand(command);
  rendertext.Commit();
}



}

BlockSelectionController::BlockSelectionController(RenderText& rendertext, Character& begin, Character& end, CaretPosition pos)
    : rendertext_(rendertext),
      selection_(begin, end, pos)

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
  SetRunProp(rendertext_, selection_, &RunProp::SetBold, &RunProp::GetBold, bold);
}

void BlockSelectionController::SetItalic(bool italic) 
{
  SetRunProp(rendertext_, selection_, &RunProp::SetItalic, &RunProp::GetItalic, italic);
}

void BlockSelectionController::SetSize(int size) 
{
  SetRunProp(rendertext_, selection_, &RunProp::SetSize, &RunProp::GetSize, size);
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
  auto start = selection_.GetStart();
  auto end = selection_.GetEnd();
  auto pos = selection_.GetCaretPosition();
  if( event.GetFlag(kControlDown) ) {
    if( event.GetCode() == KeyboardCode::VKEY_Z )
      rendertext_.GetCommitTree()->UnDo();
    else if( event.GetCode() == KeyboardCode::VKEY_Y )
      rendertext_.GetCommitTree()->ReDo();

  } else if( event.GetFlag(kShiftDown) ) {
    if( event.GetCode() == KeyboardCode::VKEY_RIGHT ) {
      if( selection_.GetCaretPosition() == CaretPosition::kStart ) {
        auto next = start->GetNextCharacter();
        if( next ) {
          auto command = new SetSelectionCommand(
              &rendertext_,
              selection_util::createTextSelection(&rendertext_, next, end, pos));

          rendertext_.GetCommitTree()->AddCommand(command);
        }
      } else {
        auto next = end->GetNextCharacter();
        if( next ) {
          auto command = new SetSelectionCommand(
              &rendertext_,
              selection_util::createTextSelection(&rendertext_,start, next, pos));

          rendertext_.GetCommitTree()->AddCommand(command);
        }
      }
    } else if( event.GetCode() == KeyboardCode::VKEY_LEFT ) {
      if( selection_.GetCaretPosition() == CaretPosition::kStart ) {
        auto prev = start->GetPrevCharacter();
        if( prev ) {
          auto command = new SetSelectionCommand(
              &rendertext_,
              std::make_shared<BlockSelectionController>(rendertext_, *prev, *end, pos));

          rendertext_.GetCommitTree()->AddCommand(command);
        }

      } else {
        auto prev = end->GetPrevCharacter();
        if( prev ) {
          auto command = new SetSelectionCommand(
              &rendertext_,
              selection_util::createTextSelection(&rendertext_, start, prev, pos));

          rendertext_.GetCommitTree()->AddCommand(command);
        }

      }
    } else if( event.GetCode() == KeyboardCode::VKEY_UP ) {
      auto hitted = selection_util::GetHittedChar(selection_.GetCaret(), selection_.GetX(), &LineView::GetPrevSibling);
      auto command = new SetSelectionCommand(
          &rendertext_,
          selection_util::createSelection(&rendertext_, hitted, selection_.GetTail()));

      rendertext_.GetCommitTree()->AddCommand(command);
      
    } else if( event.GetCode() == KeyboardCode::VKEY_DOWN ) {
      auto hitted = selection_util::GetHittedChar(selection_.GetCaret(), selection_.GetX(), &LineView::GetNextSibling);
      auto command = new SetSelectionCommand(
          &rendertext_,
          selection_util::createSelection(&rendertext_, hitted, selection_.GetTail()));

      rendertext_.GetCommitTree()->AddCommand(command);
    }

    
  } else if ( event.GetCode() == KeyboardCode::VKEY_LEFT ) {
    auto command = new SetSelectionCommand(
        &rendertext_,
        selection_util::createTextSelection(&rendertext_, start, start, pos));
    rendertext_.GetCommitTree()->AddCommand(command);
    
  } else if ( event.GetCode() == KeyboardCode::VKEY_RIGHT ) {
    auto command = new SetSelectionCommand(
        &rendertext_,
        selection_util::createTextSelection(&rendertext_, end, end, pos));
    rendertext_.GetCommitTree()->AddCommand(command);
    
  } else if ( event.GetCode() == KeyboardCode::VKEY_UP ) {
    selection_util::ProcessUpDownKey(&rendertext_, selection_.GetCaret(), selection_.GetX(), &LineView::GetPrevSibling);
  } else if ( event.GetCode() == KeyboardCode::VKEY_DOWN ) {
    selection_util::ProcessUpDownKey(&rendertext_, selection_.GetCaret(), selection_.GetX(), &LineView::GetNextSibling);
  } else if ( event.GetCode() == KeyboardCode::VKEY_BACK ) {
    auto selected = selection_.GetEnd();
    auto front = selection_.GetStart()->GetPrevCharacter();
    while( selected->GetPrevCharacter() != front ) {
      auto command = new DeleteCharCommand(selected);
      rendertext_.GetCommitTree()->AddCommand(command);
      //selected = selected->GetPrevCharacter();
    }

    auto command = new SetSelectionCommand(
        &rendertext_,
        selection_util::createTextSelection(&rendertext_, end, end, pos));
    rendertext_.GetCommitTree()->AddCommand(command);

    rendertext_.GetCommitTree()->DoCommit();
  } else if ( event.GetChar() != 0 ) {
    rendertext_.GetCommitTree()->AddCommand(new DeleteTextCommand(selection_.GetStart(), selection_.GetEnd()));
    
    auto character = CreateCharacter(event.GetChar());
    rendertext_.GetCommitTree()->AddCommand(new InsertCharCommand(character, selection_.GetEnd()));

    auto command = new SetSelectionCommand(
        &rendertext_,
        selection_util::createSelection(&rendertext_, selection_.GetEnd(), selection_.GetEnd()));
    rendertext_.GetCommitTree()->AddCommand(command);
    
    rendertext_.GetCommitTree()->DoCommit();

  }
}

void BlockSelectionController::Paint(Canvas& canvas)
{
  selection_.GetView().Paint(canvas);  
}
void BlockSelectionController::Layout()
{
  selection_.GetView().Layout();
}


}  // le



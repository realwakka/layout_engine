#include "caret_controller.h"

#include "model/selection/selection_util.h"
#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"
#include "model/selection/caret_selection.h"
#include "model/selection/block_selection.h"

#include "view/hititem.h"
#include "view/line_view.h"

#include "controller/block_selection_controller.h"
#include "controller/event/mouse_event.h"

#include "controller/event/key_event.h"
#include "controller/command/insert_char_command.h"
#include "controller/command/delete_char_command.h"
#include "controller/command/set_selection_command.h"
#include "controller/command/commit_tree.h"
#include "controller/command/run_prop/set_run_prop_command.h"

#include "render_text.h"

#include <iostream>
#include <memory>

namespace le {
namespace {

template<typename Func>
Character* GetHittedChar(Character* character, int x, Func func)
{
  auto lineview = character->GetView().GetLineView();
  auto prevline = (lineview->*func)();

  if( prevline ) {
    auto abspos = prevline->GetAbsolutePosition();
    Point point(x, abspos.GetY());
    HitItem item;
    prevline->GetLayer()->HitTest(item , point);
    auto hitted = item.GetView();

    if( hitted && typeid(*hitted) == typeid(CharacterView) ) {
      auto& hitted_char = static_cast<CharacterView*>(hitted)->GetCharacter();
      return &hitted_char;
    }
  }
  return nullptr;
}

template<typename Func>
void ProcessShiftVertKey(RenderText* rendertext, CaretSelection* selection, Func func, CaretPosition pos)
{
  auto hitted = GetHittedChar(&selection->GetCharacter(), selection->GetX(), func);
  
  if( hitted ) {
    std::shared_ptr<Controller> controller;
    if( pos == CaretPosition::kEnd )
      controller = std::make_shared<BlockSelectionController>(*rendertext, selection->GetCharacter(), *hitted, pos);
    else 
      controller = std::make_shared<BlockSelectionController>(*rendertext, *hitted, selection->GetCharacter(), pos);

    auto command = new SetSelectionCommand( rendertext, controller );
    rendertext->GetCommitTree()->AddCommand(command);
  }
}

// void ProcessShiftUpKey(RenderText* rendertext, CaretSelection* selection)
// {
//   auto hitted = GetHittedChar(selection, &LineView::GetPrevSibling);
  
//   if( hitted ) {
//     auto controller = std::make_shared<BlockSelectionController>(*rendertext, *hitted, selection->GetCharacter(), CaretPosition::kStart);

//     auto command = new SetSelectionCommand( rendertext, controller );
//     rendertext->GetCommitTree()->AddCommand(command);
//   }
// }

// void ProcessShiftDownKey(RenderText* rendertext, CaretSelection* selection)
// {
//   auto hitted = GetHittedChar(selection, &LineView::GetNextSibling);
  
//   if( hitted ) {
//     auto controller = std::make_shared<BlockSelectionController>(*rendertext, selection->GetCharacter(), *hitted, CaretPosition::kEnd);

//     auto command = new SetSelectionCommand( rendertext, controller );
//     rendertext->GetCommitTree()->AddCommand(command);
//   }
// }




// template<typename Func>
// void ProcessUpDownKey(RenderText* rendertext, CaretSelection* selection, Func func)
// {
//   auto hitted = GetHittedChar(&selection->GetCharacter(), selection->GetX(), func);

//   if( hitted ) {
//       auto command = new SetSelectionCommand(
//           rendertext,
//           std::make_shared<CaretController>(*hitted, selection->GetX(), rendertext));
      
//       rendertext->GetCommitTree()->AddCommand(command);
//   }
// }

void ProcessHorzKey(RenderText* rendertext, Character* next)
{
  if( next ) {
    auto new_sel = std::make_shared<CaretController>(*next, rendertext);
    auto command = new SetSelectionCommand(
        rendertext,
        std::make_shared<CaretController>(*next, rendertext));

    rendertext->GetCommitTree()->AddCommand(command);
  }
}

template<typename Setter, typename Getter, typename Value>
void ProcessRunProp(RenderText* rendertext, Character* selected, Setter&& setter, Getter&& getter, Value&& value)
{
  if( typeid(*selected) == typeid(BasicCharacter) ) {
    rendertext->Commit();
    
    auto word = selected->GetWord();
    auto begin = word->GetFirstCharacter();
    auto end = word->GetFirstSpaceCharacter();

    auto command = command_util::CreateSetRunPropCommand(begin, end, setter, getter, value);
    rendertext->GetCommitTree()->AddCommand(command);
    rendertext->Commit();
    
  } else {
    auto cached = rendertext->GetCachedRun();
    if( cached == nullptr ) {
      rendertext->SetCachedRun(new TextRun());
      cached = rendertext->GetCachedRun();
    }
    (cached->GetRunProp().*setter)(value);
  }

}

}

CaretController::CaretController(Character& character, RenderText* rendertext)
    : rendertext_(rendertext),
      selection_(character)

{
  
}

CaretController::CaretController(Character& character, int x, RenderText* rendertext)
    : rendertext_(rendertext),
      selection_(character, x)
{}
CaretController::~CaretController()
{}

void CaretController::InsertText(std::string text)
{

}

void CaretController::InsertChar(Character* character)
{
  auto& selected = selection_.GetCharacter();
  auto paragraph = selected.GetRun()->GetParagraph();
  auto command = new InsertCharCommand(character, &selected);
  rendertext_->GetCommitTree()->AddCommand(command);
}

void CaretController::BackSpaceChar()
{
  // auto paragraph = enter_char_.GetRun()->GetParagraph();

  // BackSpaceWordInternal(*paragraph);
  // BackSpaceRunInternal(*paragraph);
}

void CaretController::SetBold(bool bold)
{
  ProcessRunProp(rendertext_, &selection_.GetCharacter(), &RunProp::SetBold, &RunProp::GetBold, bold);
}

void CaretController::SetItalic(bool italic)
{
  ProcessRunProp(rendertext_, &selection_.GetCharacter(), &RunProp::SetItalic, &RunProp::GetItalic, italic);
}

void CaretController::SetSize(int size)
{
  ProcessRunProp(rendertext_, &selection_.GetCharacter(), &RunProp::SetSize, &RunProp::GetSize, size);
}

void CaretController::SetPageSize(int width, int height)
{
  auto paragraph = selection_.GetCharacter().GetRun()->GetParagraph();
  auto& sectionprop = paragraph->GetParent()->GetSectionProp();
  sectionprop.GetPageSize().SetWidth(width);
  sectionprop.GetPageSize().SetHeight(height);
}

void CaretController::OnMousePressed(const MouseEvent& event)
{
  auto document = selection_.GetCharacter().GetRun()->GetParagraph()->GetParent();
  auto& view = document->GetView();

  Point point(event.GetX(), event.GetY());
  HitItem item;
  if( view.GetLayer()->HitTest(item, point) ) {
    std::cout << "clicked : " << typeid(*item.GetView()).name() << std::endl;
  } else {
    std::cout << "no clicked" << std::endl;
  }
  
}

void CaretController::OnKeyDown(const KeyEvent& event)
{
  std::cout << "KEY DOWN" << std::endl;
  std::cout << "KEY : " << event.GetChar() << std::endl;

  if( event.GetFlag(kControlDown) ) {
    if( event.GetCode() == KeyboardCode::VKEY_Z )
      rendertext_->GetCommitTree()->UnDo();
    else if( event.GetCode() == KeyboardCode::VKEY_Y )
      rendertext_->GetCommitTree()->ReDo();

  } else if( event.GetFlag(kShiftDown) ) {
    if( event.GetCode() == KeyboardCode::VKEY_RIGHT ) {
      auto next = selection_.GetCharacter().GetNextCharacter();
      if( next ) {
        auto command = new SetSelectionCommand(
            rendertext_,
            std::make_shared<BlockSelectionController>(*rendertext_, selection_.GetCharacter(), *next, CaretPosition::kEnd));

        rendertext_->GetCommitTree()->AddCommand(command);
      }

    } else if( event.GetCode() == KeyboardCode::VKEY_LEFT ) {
      auto prev = selection_.GetCharacter().GetPrevCharacter();
      if( prev ) {
        auto command = new SetSelectionCommand(
            rendertext_,
            std::make_shared<BlockSelectionController>(*rendertext_, *prev, selection_.GetCharacter(), CaretPosition::kStart));

        rendertext_->GetCommitTree()->AddCommand(command);
      }


    } else if( event.GetCode() == KeyboardCode::VKEY_DOWN ) {
      ProcessShiftVertKey(rendertext_, &selection_, &LineView::GetNextSibling, CaretPosition::kEnd);
    } else if( event.GetCode() == KeyboardCode::VKEY_UP ) {
      ProcessShiftVertKey(rendertext_, &selection_, &LineView::GetPrevSibling, CaretPosition::kStart);
    }
  } else if( event.GetChar() != 0 ) {
    auto character = CreateCharacter(event.GetChar());
    auto paragraph = selection_.GetCharacter().GetRun()->GetParagraph();

    auto command = new InsertCharCommand(character, &selection_.GetCharacter());
    rendertext_->GetCommitTree()->AddCommand(command);

  } else {
    switch( event.GetCode() ) {
      case KeyboardCode::VKEY_BACK: {
        auto command = new DeleteCharCommand(&selection_.GetCharacter());
        rendertext_->GetCommitTree()->AddCommand(command);
        break;
      }
      case KeyboardCode::VKEY_RIGHT: {
        ProcessHorzKey(rendertext_, selection_.GetCharacter().GetNextCharacter());
        break;
      }
      case KeyboardCode::VKEY_LEFT: {
        ProcessHorzKey(rendertext_, selection_.GetCharacter().GetPrevCharacter());
        break;
      }
      case KeyboardCode::VKEY_UP: {
        selection_util::ProcessUpDownKey(rendertext_, &selection_.GetCharacter(), selection_.GetX(), &LineView::GetPrevSibling);
        break;
      }
      case KeyboardCode::VKEY_DOWN: {
        selection_util::ProcessUpDownKey(rendertext_, &selection_.GetCharacter(), selection_.GetX(), &LineView::GetNextSibling);
        break;
      }
      
    }

  }

}

void CaretController::Paint(Canvas& canvas)
{
  selection_.GetView().Paint(canvas);
}
void CaretController::Layout()
{
  selection_.GetView().Layout();
}


}  // le

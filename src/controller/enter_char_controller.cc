#include "enter_char_controller.h"

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"
#include "controller/event/mouse_event.h"
#include "view/hititem.h"
#include "controller/event/key_event.h"
#include "controller/command/insert_char_command.h"

#include <iostream>

namespace le {

namespace {

void BackSpaceWordInternal(Paragraph& paragraph)
{
  auto last_word = paragraph.GetLastWord();
  if( last_word == nullptr ) {

  } else {
    auto prev_char = last_word->GetLastCharacter();
    last_word->RemoveCharacter(prev_char);

    if( last_word->GetFirstCharacter() == nullptr )
      paragraph.RemoveWord(last_word);
  }
}

void BackSpaceRunInternal(Paragraph& paragraph)
{
  auto last_run = paragraph.GetLastRun();
  if( last_run == nullptr ) {

  } else {
    auto prev_char = last_run->GetLastCharacter();
    last_run->RemoveCharacter(prev_char);

    if( last_run->GetFirstCharacter() == nullptr )
      paragraph.RemoveRun(last_run);
  }
}

}


EnterCharController::EnterCharController(EnterCharacter& enter_char)
    : enter_char_(enter_char)
{}
EnterCharController::~EnterCharController()
{}

void EnterCharController::InsertText(std::string text)
{

}

void EnterCharController::InsertChar(Character* character)
{
  auto paragraph = enter_char_.GetRun()->GetParagraph();

  // auto stack = CommandStack::GetInstance();
  // stack->DoCommand<InsertCharCommand>(paragraph, nullptr, character);
}

void EnterCharController::BackSpaceChar()
{
  auto paragraph = enter_char_.GetRun()->GetParagraph();

  BackSpaceWordInternal(*paragraph);
  BackSpaceRunInternal(*paragraph);
}

void EnterCharController::SetBold(bool bold)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetBold(bold);
}

void EnterCharController::SetItalic(bool italic)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetItalic(italic);
}

void EnterCharController::SetSize(int size)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetSize(size);
}

void EnterCharController::SetPageSize(int width, int height)
{
  auto paragraph = enter_char_.GetRun()->GetParagraph();
  auto& sectionprop = paragraph->GetParent()->GetSectionProp();
  sectionprop.GetPageSize().SetWidth(width);
  sectionprop.GetPageSize().SetHeight(height);
}

void EnterCharController::OnMousePressed(const MouseEvent& event)
{
  auto document = enter_char_.GetRun()->GetParagraph()->GetParent();
  auto& view = document->GetView();

  Point point(event.GetX(), event.GetY());
  HitItem item;
  if( view.GetLayer()->HitTest(item, point) ) {
    std::cout << "clicked : " << typeid(*item.GetView()).name() << std::endl;
  } else {
    std::cout << "no clicked" << std::endl;
  }
  
}

void EnterCharController::OnKeyDown(const KeyEvent& event)
{
  std::cout << "KEY DOWN" << std::endl;
  std::cout << "KEY : " << event.GetChar() << std::endl;

  if( event.GetCtrlDown() || event.GetCtrlDown() ) {
    
    if( event.GetCtrlDown() && event.GetCode() == KeyboardCode::VKEY_Z ) {
      // CommandStack::GetInstance()->UndoCommand();
    }
  } else if( event.GetChar() != 0 ) {
    auto character = CreateCharacter(event.GetChar());
    auto paragraph = enter_char_.GetRun()->GetParagraph();
    // auto stack = CommandStack::GetInstance();
    // stack->DoCommand<InsertCharCommand>(paragraph, nullptr, character);
  } else {
    switch( event.GetCode() ) {
      case KeyboardCode::VKEY_BACK:
      
        break;
      case KeyboardCode::VKEY_RIGHT:

        break;
      case KeyboardCode::VKEY_LEFT:

        break;
      
    }

  }

}

}  // le

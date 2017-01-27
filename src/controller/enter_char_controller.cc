#include "enter_char_controller.h"

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"
#include "controller/event/mouse_event.h"
#include "view/hititem.h"

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

void InsertWordInternal(Paragraph* paragraph, Character* character)
{
  auto last_word = paragraph->GetLastWord();
  
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);
    last_word->InsertCharacter(character, nullptr);
  } else {
    
    auto prev_char = last_word->GetLastCharacter();
    if( typeid(*character) == typeid(BasicCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if ( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
    } else if (typeid(*character) == typeid(SpaceCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
      
    } else {

    }
  }

}

void InsertRunInternal(Paragraph* paragraph, Character* character)
{
  auto cached = Run::GetCachedRun();
  if( cached ) {
    paragraph->InsertRun(cached, nullptr);
  }
  
  auto last_run =  paragraph->GetLastRun();

  if(last_run == nullptr) {
    last_run = new TextRun();
    paragraph->InsertRun(last_run, nullptr);
  }
  
  last_run->InsertCharacter(character, nullptr);

  Run::SetCachedRun(nullptr);
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

  InsertWordInternal(paragraph, character);
  InsertRunInternal(paragraph, character);
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
}

}  // le

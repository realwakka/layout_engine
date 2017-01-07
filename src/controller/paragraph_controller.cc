#include "paragraph_controller.h"

#include "model/text_run.h"
#include "model/character/character.h"
#include "model/character/space_character.h"
#include "model/character/basic_character.h"
#include "model/selection/caret_selection.h"
#include "controller/controller.h"

namespace le {

namespace {

Character* createCharacter(char ch)
{
  switch(ch) {
    case ' ':
      return new SpaceCharacter();
    default:
      return new BasicCharacter(ch);
  }
}

}

ParagraphController::ParagraphController()
    : selected_char_(paragraph_.GetEnterRun()->GetEnterChar()),
      selection_(new CaretSelection(*paragraph_.GetEnterRun()->GetEnterChar()))
{
  
}

ParagraphController::~ParagraphController()
{

}

void ParagraphController::InsertText(std::string text)
{
  for( char c : text ) {
    auto character = createCharacter(c);
    selection_->GetController()->InsertChar(character);
    paragraph_.PrintInfo();
  }
  paragraph_.GetFirstRun()->UpdateGlyph();
}

void ParagraphController::SetBold(bool bold)
{
  selection_->GetController()->SetBold(bold);
}

void ParagraphController::SetItalic(bool italic)
{
  selection_->GetController()->SetItalic(italic);
}

void ParagraphController::SetSize(int size)
{
  selection_->GetController()->SetSize(size);
}


void ParagraphController::Layout()
{
  paragraph_.GetView().Layout();
}



}  // tmaxoffice

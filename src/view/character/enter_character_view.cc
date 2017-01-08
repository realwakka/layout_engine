#include "view/character/enter_character_view.h"

#include "model/character/enter_character.h"
#include <iostream>

namespace le {

EnterCharacterView::EnterCharacterView(EnterCharacter& enter_character)
    : CharacterView(enter_character)
{}

EnterCharacterView::~EnterCharacterView()
{}

void EnterCharacterView::Layout()
{
  std::cout << "enter character view layout" << std::endl;
}
void EnterCharacterView::Paint(Canvas& canvas)
{
  std::cout << "enter character view layout" << std::endl;
}



}  // le

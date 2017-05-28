#ifndef LE_SELECTION_UTIL_H_
#define LE_SELECTION_UTIL_H_

#include <memory>

#include "render_text.h"
#include "controller/command/set_selection_command.h"
#include "controller/caret_controller.h"
#include "model/character/character.h"
#include "view/hititem.h"

namespace le {

class Selection;
class Character;
enum class CaretPosition;
class Controller;
class RenderText;

namespace selection_util {

std::shared_ptr<Controller> createTextSelection(RenderText* rendertext, Character* start, Character* end, CaretPosition pos);

std::shared_ptr<Controller> createSelection(RenderText* rendertext, Character* src, Character* dst);

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
void ProcessUpDownKey(RenderText* rendertext, Character* character, int x, Func func)
{
  auto hitted = GetHittedChar(character, x, func);

  if( hitted ) {
      auto command = new SetSelectionCommand(
          rendertext,
          std::make_shared<CaretController>(*hitted, x, rendertext));
      
      rendertext->GetCommitTree()->AddCommand(command);
  }
}



}  // selection_util
}  // le

#endif /* LE_SELECTION_UTIL_H_ */


#ifndef LE_SELECTION_UTIL_H_
#define LE_SELECTION_UTIL_H_

#include <memory>

namespace le {

class Selection;
class Character;
enum class CaretPosition;
class Controller;
class RenderText;

namespace selection_util {

std::shared_ptr<Controller> createTextSelection(RenderText* rendertext, Character* start, Character* end, CaretPosition pos);

}  // selection_util
}  // le

#endif /* LE_SELECTION_UTIL_H_ */


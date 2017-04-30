#ifndef LE_WEB_PAINTER_H_
#define LE_WEB_PAINTER_H_

#include <vector>

namespace le {

class RenderText;

namespace web {

class Painter
{
 public:
  Painter();
  virtual ~Painter();

  std::vector<unsigned char> PaintToPng(RenderText& rendertext);
  
};


}  // web
}  // le

#endif /* LE_WEB_PAINTER_H_ */

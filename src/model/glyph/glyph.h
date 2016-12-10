#ifndef LE_GLYPH_H_
#define LE_GLYPH_H_

#include <freetype/ftglyph.h>

namespace le {

class Glyph
{
 public:
  Glyph();
  Glyph(FT_Glyph ft_glyph_);
  virtual ~Glyph();

 private:
  FT_Glyph ft_glyph_;

};

}  // le

#endif /* LE_GLYPH_H_ */

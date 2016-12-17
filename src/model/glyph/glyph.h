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

  int GetAdvanceX() const;
  int GetAdvanceY() const;

  int GetBitmapWidth() const;
  int GetBitmapHeight() const;
  
  int GetLeft() const;
  int GetTop() const;

  const unsigned char* GetBitmapBuffer() const;

 private:
  FT_Glyph ft_glyph_;

};

}  // le

#endif /* LE_GLYPH_H_ */

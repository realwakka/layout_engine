#ifndef LE_FACE_H_
#define LE_FACE_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype/freetype.h>
#include <string>

#include <unordered_map>
#include <memory>

namespace le {
class Glyph;

class Face
{
 public:
  Face();
  explicit Face(FT_Face ft_face);
  virtual ~Face();

  int GetHeight() const;
  int GetAscender() const;
  
 private:
  FT_Face ft_face_;
};

}  // le


#endif /* LE_FACE_H_ */


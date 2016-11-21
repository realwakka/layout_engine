#ifndef LE_FACE_H_
#define LE_FACE_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype/freetype.h>

namespace le {

class Face
{
 public:
  Face(FT_Face ft_face);
  virtual ~Face();
  

 private:
  FT_Face ft_face_;
  
};


}  // le


#endif /* LE_FACE_H_ */


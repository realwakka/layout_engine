#include "face.h"

namespace le {

Face::Face()
{
  FT_Library library;
  if (FT_Init_FreeType(&library)) {
    exit(0);
  }
  //load default NanumGothic.ttf
  FT_New_Face(library,"../NanumGothic.ttf",0,&ft_face_);
  

}

Face::~Face()
{}


}  // le

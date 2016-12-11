#include "face.h"

#include "model/glyph/glyph.h"

namespace le {

Face::Face()
{
  
}

Face::Face(FT_Face ft_face)
    : ft_face_(ft_face)
{
  
}

Face::~Face()
{}


}  // le

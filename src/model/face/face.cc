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

int Face::GetHeight() const
{
  return ft_face_->size->metrics.height >> 6;
}

int Face::GetAscender() const
{
  return ft_face_->size->metrics.ascender >> 6;
}


}  // le

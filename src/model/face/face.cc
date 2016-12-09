#include "face.h"

#include "model/glyph/glyph.h"

namespace le {

Face::Face(FT_Face ft_face)
    : ft_face_(ft_face)
{
  
}

Face::Face(std::string family, int size)
    : family_(family),
      size_(size)
{
  
}

Face::~Face()
{}

Glyph Face::GetGlyph()
{

}

}  // le

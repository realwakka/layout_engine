#include "face.h"

#include "model/glyph/glyph.h"
#include "model/face/face_manager.h"

namespace le {

Face::Face()
{
  ft_face_ = FaceManager::GetInstance()->GetDefaultFace().ft_face_;
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

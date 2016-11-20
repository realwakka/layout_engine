#include "face_manager.h"

#include "face.h"

namespace le {

FaceManager* FaceManager::instance_ = nullptr;

FT_Error my_face_requester( FTC_FaceID   face_id,
                            FT_Library   library,
                            FT_Pointer   request_data,
                            FT_Face     *aface )
{
  return FT_New_Face( library, "../NanumGothic.ttf", 0, aface );
}

FaceManager* FaceManager::GetInstance()
{
  if( instance_ == nullptr )
    instance_ = new FaceManager();

  return instance_;
}

FaceManager::FaceManager()
{
  auto error = FTC_Manager_New(ft_library_, 0, 0, 0, &my_face_requester, nullptr, &ft_manager_ );

  FTC_CMapCache_New( ft_manager_, &ft_cmapcache_);
  FTC_ImageCache_New( ft_manager_, &ft_imgcache_);
}

FaceManager::~FaceManager()
{
  
}

Face FaceManager::GetFace(char c)
{
  auto glyph_idx = FTC_CMapCache_Lookup(ft_cmapcache_, 0, 0, c);

  FTC_ImageType img;
  FT_Glyph glyph;
  FTC_Node node;
  FTC_ImageCache_Lookup( ft_imgcache_, img, glyph_idx, &glyph, &node );

  
}


}  // le

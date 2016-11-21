#include "face_manager.h"

#include "face.h"

namespace le {

FaceManager* FaceManager::instance_ = nullptr;

FT_Error FaceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer request_data, FT_Face *aface )
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
  auto error = FTC_Manager_New(ft_library_, 0, 0, 0, &FaceRequester, nullptr, &ft_manager_ );

  FTC_CMapCache_New( ft_manager_, &ft_cmapcache_);
  FTC_ImageCache_New( ft_manager_, &ft_imgcache_);
}

FaceManager::~FaceManager()
{
  
}

Face FaceManager::GetDefaultFace()
{
  FT_Face ft_face;
  FTC_FaceID faceid = new FaceId();
  FTC_Manager_LookupFace( ft_manager_, faceid, &ft_face );
  
  Face face(ft_face);
  return face;
}

}  // le

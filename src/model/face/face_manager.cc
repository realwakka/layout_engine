#include "face_manager.h"

#include <fontconfig/fontconfig.h>
#include <fontconfig/fcfreetype.h>

#include <exception>

#include "face.h"


namespace le {

FaceManager* FaceManager::instance_ = nullptr;

FT_Error FaceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer request_data, FT_Face *aface )
{
  FcPattern *pat = FcPatternCreate();
  FcChar8* family = FcStrCopy(static_cast<const FcChar8*>(face_id));
  FcPatternAddString( pat, "family", family );

  FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, FC_SIZE, FC_OUTLINE, FC_LANG, FC_FILE, FC_CHARSET, FC_FONT_FEATURES, FC_FT_FACE, (char *) 0);
  FcFontSet *fs = FcFontList(nullptr, pat, os);

  if( fs->nfont ) {
    

  }
  else {
    //throw std::exception;
  }

  
  return 0;
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

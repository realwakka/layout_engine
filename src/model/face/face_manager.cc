#include "face_manager.h"

#include <fontconfig/fontconfig.h>
#include <fontconfig/fcfreetype.h>

#include <exception>
#include <string>
#include <iostream>

#include "face.h"


namespace le {

FaceManager* FaceManager::instance_ = nullptr;

FT_Error FaceRequester( FTC_FaceID face_id, FT_Library library, FT_Pointer request_data, FT_Face *aface )
{
  auto pat = FcPatternCreate();
  
  //auto family = FcStrCopy(static_cast<const FcChar8*>(face_id));
  auto family = static_cast<std::string*>(face_id);
  FcPatternAddString( pat, "family", reinterpret_cast<const FcChar8*>(family->c_str()) );
  auto os = FcObjectSetBuild(FC_FAMILY, FC_FILE, FC_FT_FACE, (char *) 0);
  auto fs = FcFontList(nullptr, pat, os);

  if( fs->nfont ) {
    auto pattern = fs->fonts[0];
    FT_Face face;
    FcResult result = FcPatternGetFTFace(pattern, FC_FT_FACE, 0, &face);
    std::cout << result << std::endl;

    char* file;
    result = FcPatternGetString(pattern, "file", 0, (FcChar8**)&file);
    std::cout << result << std::endl;
    return FT_New_Face( library, file, 0, aface );

  }
  else {
    throw std::exception{};
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
  auto error = FT_Init_FreeType( &ft_library_ );
  error = FTC_Manager_New(ft_library_, 0, 0, 0, &FaceRequester, nullptr, &ft_manager_ );

  FTC_CMapCache_New( ft_manager_, &ft_cmapcache_);
  FTC_ImageCache_New( ft_manager_, &ft_imgcache_);
}

FaceManager::~FaceManager()
{
  
}

Face* FaceManager::GetDefaultFace()
{
  FT_Face ft_face;
  std::string family_name = "Times new roman";
  FTC_FaceID faceid = &family_name;
  FTC_Manager_LookupFace( ft_manager_, faceid, &ft_face );
  
  auto face = new Face(ft_face);
  return face;
}

}  // le

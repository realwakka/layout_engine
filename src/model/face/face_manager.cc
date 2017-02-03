#include "face_manager.h"

#include <fontconfig/fontconfig.h>
#include <fontconfig/fcfreetype.h>

#include <exception>
#include <string>
#include <iostream>

#include "face.h"
#include "model/glyph/glyph.h"
#include "model/prop/run_prop.h"
#include "model/character/character.h"

#include <freetype/ftoutln.h>

namespace le {

FaceManager* FaceManager::instance_ = nullptr;

FaceManager* FaceManager::GetInstance()
{
  if( instance_ == nullptr ) {
    instance_ = new FaceManager();
    instance_->LoadSystemFaces();
  }
  
  return instance_;
}

FaceManager::FaceManager()
{
  auto error = FT_Init_FreeType( &ft_library_ );
  // error = FTC_Manager_New(ft_library_, 0, 0, 0, &FaceRequester, nullptr, &ft_manager_ );

  // FTC_CMapCache_New( ft_manager_, &ft_cmapcache_);
  // FTC_ImageCache_New( ft_manager_, &ft_imgcache_);
}

FaceManager::~FaceManager()
{
  
}

std::pair<std::string, int> FaceManager::CreateFaceCacheKey(std::string path, int index)
{
  return std::make_pair(path, index);
}

void FaceManager::LoadSystemFaces()
{
  auto pat = FcPatternCreate();
  
  auto os = FcObjectSetBuild(FC_FILE, FC_FT_FACE, FC_LANG, nullptr);
  auto fs = FcFontList(nullptr, pat, os);

  for(int i=0 ; i<fs->nfont ; ++i ) {
    auto pattern = fs->fonts[i];
    FT_Face ft_face = nullptr;
    FcResult result = FcPatternGetFTFace(pattern, FC_FT_FACE, 0, &ft_face);
    char* path = nullptr;
    result = FcPatternGetString(pattern, "file", 0, (FcChar8**)&path);
    auto res = FT_New_Face( ft_library_, path, 0, &ft_face );

    auto key = CreateFaceCacheKey(path, 0);
    face_cache_map_.emplace(key, ft_face);
    
    if( default_face_ == nullptr ) {
      FcLangSet* langset = nullptr;
      auto result = FcPatternGetLangSet(pattern, "lang", 0, &langset);
      if( result == FcResultMatch ) {
        auto en_result = FcLangSetHasLang(langset, reinterpret_cast<const unsigned char*>("en"));
        if ( en_result == FcLangEqual )
          default_face_ = ft_face;
      }

    }
  }
}

Face FaceManager::GetDefaultFace()
{
  return Face(default_face_);
}


Face FaceManager::GetFace(const RunProp& runprop)
{
  auto pat = FcPatternCreate();
  
  //FcPatternAddString( pat, "family", reinterpret_cast<const FcChar8*>(face.GetFamily().c_str()) );
  auto langset = FcLangSetCreate();
  FcLangSetAdd(langset, reinterpret_cast<const FcChar8*>("en"));
  FcPatternAddLangSet(pat, "lang", langset);
  auto os = FcObjectSetBuild(FC_FAMILY,FC_FILE, FC_FT_FACE, nullptr);
  auto fs = FcFontList(nullptr, pat, os);

  if( fs->nfont ) {
    FT_Face ft_face = nullptr;
    auto pattern = fs->fonts[0];
    FcResult result = FcPatternGetFTFace(pattern, FC_FT_FACE, 0, &ft_face);
    
    char* file = nullptr;
    result = FcPatternGetString(pattern, "file", 0, (FcChar8**)&file);
    auto res = FT_New_Face( ft_library_, file, 0, &ft_face );
    
    FT_Set_Char_Size(ft_face, runprop.GetSize() << 6 , 0, 96,96);

    return Face(ft_face);
  }
  else {
    throw std::exception();
  }
}

Glyph FaceManager::GetGlyph(const RunProp& runprop, const Character& character)
{
  FT_Face ft_face = runprop.GetFont().GetPrimaryFont().ft_face_;
  FT_Set_Char_Size(ft_face, runprop.GetSize() << 6 , 0, 96,96);

  auto index = FT_Get_Char_Index(ft_face,character.GetChar());
  auto error = FT_Load_Glyph( ft_face, index, FT_LOAD_NO_BITMAP );

  FT_Glyph ft_glyph;
  error = FT_Get_Glyph( ft_face->glyph, &ft_glyph );

  if( runprop.GetBold() ) {
    auto outline_glyph = reinterpret_cast<FT_OutlineGlyph>(ft_glyph);
    FT_Outline_Embolden( &outline_glyph->outline, (ft_face->size->metrics.x_ppem*5/100) << 6);
  }

  if( runprop.GetItalic() ) {
    auto outline_glyph = reinterpret_cast<FT_OutlineGlyph>(ft_glyph);
    FT_Matrix transform = {0x10000, 0x06000, 0x00000, 0x10000};
    FT_Outline_Transform( &outline_glyph->outline, &transform );
  }

  return Glyph(ft_glyph);
}

}  // le

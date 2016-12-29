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
  if( instance_ == nullptr )
    instance_ = new FaceManager();

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
    //return res;

  }
  else {
    throw std::exception{};
  }
  

  
  // std::string family_name = "Times new roman";

  // auto family = new std::string("Times new roman");
  // auto index = FTC_CMapCache_Lookup(ft_cmapcache_,family,0,character.GetChar());

  // FTC_Node ftc_node;
  // // FTC_SBit ftc_sbit;
  
  // FTC_ImageType ft_image_type = new FTC_ImageTypeRec_();
  // FT_Glyph ft_glyph;
  
  // ft_image_type->face_id = &family_name;
  // ft_image_type->width = 32;
  // ft_image_type->height = 32;
  // ft_image_type->flags = FT_LOAD_DEFAULT | FT_LOAD_RENDER;
  
  // auto ret = FTC_ImageCache_Lookup(ft_imgcache_, ft_image_type, index, &ft_glyph, &ftc_node);

  // return Glyph(ft_glyph);
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

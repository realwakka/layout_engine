#ifndef LE_FACE_MANAGER_H_
#define LE_FACE_MANAGER_H_

#include "freetype/ftcache.h"
#include "face.h"
#include <string>
#include <unordered_map>
#include <map>
#include <utility>


namespace le {

class Character;
class RunProp;



class FaceManager
{
 public:
  FaceManager();
  virtual ~FaceManager();

  Glyph GetGlyph(const RunProp& runprop, const Character& character);
  Face GetFace(const RunProp& runprop);
  static FaceManager* GetInstance();

  Face GetDefaultFace();
  
 private:
  using FaceCacheKey =  std::pair<std::string, int>;

 private:
  FaceCacheKey CreateFaceCacheKey(std::string path, int index);
  void LoadSystemFaces();
  
  
 private:
  std::map<FaceCacheKey, FT_Face> face_cache_map_;
  FT_Face default_face_;
  
  static FaceManager* instance_;

  
  FTC_Manager ft_manager_;
  FT_Library ft_library_;

  FTC_CMapCache ft_cmapcache_;
  FTC_ImageCache ft_imgcache_;

  //Face default_face_;
  
};

}  // le

#endif /* LE_FACE_MANAGER_H_ */

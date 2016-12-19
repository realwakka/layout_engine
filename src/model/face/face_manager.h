#ifndef LE_FACE_MANAGER_H_
#define LE_FACE_MANAGER_H_

#include "freetype/ftcache.h"
#include "face.h"

namespace le {

class Character;
class RunProp;

class FaceManager
{
 public:
  FaceManager();
  virtual ~FaceManager();

  Face* GetDefaultFace();
  Glyph GetGlyph(const RunProp& runprop, const Character& character);
  Face GetFace(const RunProp& runprop);
  static FaceManager* GetInstance();

 private:
  static FaceManager* instance_;
  
  FTC_Manager ft_manager_;
  FT_Library ft_library_;

  FTC_CMapCache ft_cmapcache_;
  FTC_ImageCache ft_imgcache_;

  //Face default_face_;
  
};

}  // le

#endif /* LE_FACE_MANAGER_H_ */

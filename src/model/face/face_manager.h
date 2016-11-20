#ifndef LE_FACE_MANAGER_H_
#define LE_FACE_MANAGER_H_

#include "freetype2/ftcache.h"
#include "face.h"

namespace le {

class FaceManager
{
 public:
  FaceManager();
  virtual ~FaceManager();

  Face GetFace(char c);

  static FaceManager* GetInstance();

 private:
  static FaceManager* instance_;
  
  FTC_Manager ft_manager_;
  FT_Library ft_library_;

  FTC_CMapCache ft_cmapcache_;
  FTC_ImageCache ft_imgcache_;
  
};

}  // le

#endif /* LE_FACE_MANAGER_H_ */

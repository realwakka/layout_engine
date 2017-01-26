#ifndef FONT_H_
#define FONT_H_

#include "model/face/face.h"

namespace le {

class Font
{
 public:
  Font();
  virtual ~Font();

  Face GetAscii() const { return ascii_; }
  Face GetEastAsia() const { return eastasia_; }
  Face GetCs() const { return cs_; }
  Face GetHAnsi() const { return hansi_; }

  void SetAscii( Face ascii )  { ascii = ascii_; }
  void SetEastAsia( Face eastasia )  { eastasia = eastasia_; }
  void SetCs( Face cs )  { cs = cs_; }
  void SetHAnsi( Face hansi )  { hansi = hansi_; }

  const Face& GetPrimaryFont() const { return primary_; }

 private:
  Face ascii_;
  Face eastasia_;
  Face cs_;
  Face hansi_;

  Face& primary_;
};


}  // le

#endif /* FONT_H_ */

#ifndef LE_GLYPH_H_
#define LE_GLYPH_H_

#include <freetype/ftglyph.h>
#include <vector>
#include "model/glyph/span.h"

namespace le {

class Glyph
{
 public:
  Glyph();
  Glyph(FT_Glyph ft_glyph_);
  virtual ~Glyph();

  int GetAdvanceX() const;
  int GetAdvanceY() const;

  int GetBitmapWidth() const;
  int GetBitmapHeight() const;
  
  int GetLeft() const;
  int GetTop() const;


  const unsigned char* GetBitmapBuffer() const;

  std::vector<Span> GetSpanList() const { return span_list_; }
  void AddSpan(const Span& span) { span_list_.push_back(span); }

 private:
  FT_Glyph ft_glyph_;
  std::vector<Span> span_list_;

};

}  // le

#endif /* LE_GLYPH_H_ */

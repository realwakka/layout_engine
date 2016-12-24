#include "glyph.h"

#include FT_STROKER_H

namespace le {

namespace {

void RasterCallback(const int y, const int count, const FT_Span * const spans, void* const user)
{
  std::vector<Span>* sptr = (std::vector<Span>*)user;
  for (int i = 0; i < count; ++i)
    sptr->push_back(Span(spans[i].x, y, spans[i].len, spans[i].coverage));
}

}

Glyph::Glyph()
{}

Glyph::Glyph(FT_Glyph ft_glyph)
    : ft_glyph_(ft_glyph)
{

  if( ft_glyph->format == FT_GLYPH_FORMAT_OUTLINE ) {
    FT_Raster_Params params;
    memset(&params, 0, sizeof(params));
    params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
    params.gray_spans = RasterCallback;
    params.user = &span_list_;

    auto outline_glyph = reinterpret_cast<FT_OutlineGlyph>(ft_glyph);
    FT_Outline_Render(ft_glyph->library, &outline_glyph->outline, &params);
  }
  
  auto error = FT_Glyph_To_Bitmap( &ft_glyph_, FT_RENDER_MODE_NORMAL, 0, 1 );
}

Glyph::~Glyph()
{}

int Glyph::GetAdvanceX() const
{
  return ft_glyph_->advance.x >> 16;
}
int Glyph::GetAdvanceY() const
{
  return ft_glyph_->advance.y >> 16;
}

int Glyph::GetBitmapWidth() const
{
  if( ft_glyph_->format == FT_GLYPH_FORMAT_OUTLINE ) {
    throw std::exception();
  }
  else {
    FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
    return bitmap_glyph->bitmap.width;
  }
  
}

int Glyph::GetBitmapHeight() const
{
  FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
  return bitmap_glyph->bitmap.rows;
  
}

const unsigned char* Glyph::GetBitmapBuffer() const
{
  FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
  return bitmap_glyph->bitmap.buffer;

}

int Glyph::GetLeft() const
{
  FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
  return bitmap_glyph->left;
  
}

int Glyph::GetTop() const
{
  FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
  return bitmap_glyph->top;

}


}  // le

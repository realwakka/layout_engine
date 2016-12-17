#include "glyph.h"

namespace le {

Glyph::Glyph()
{}

Glyph::Glyph(FT_Glyph ft_glyph)
    : ft_glyph_(ft_glyph)
{

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
  FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph_);
  return bitmap_glyph->bitmap.width;
  
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

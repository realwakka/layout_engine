#include "glyph.h"

namespace le {

Glyph::Glyph()
{}

Glyph::Glyph(FT_Glyph ft_glyph)
    : ft_glyph_(ft_glyph)
{}

Glyph::~Glyph()
{}






}  // le

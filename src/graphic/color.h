#ifndef LE_COLOR_H_
#define LE_COLOR_H_

#include <cstdint>

namespace le {

using Color = uint32_t;

const Color AlphaTRANSPARENT=0x00;
const Color AlphaOPAQUE = 0xFF;

const Color kColorTRANSPARENT = 0x00000000;

const Color kColorBlack = 0xFF000000;
const Color kColorDkGray = 0xFF444444;
const Color kColorGray = 0xFF888888;
const Color kColorLtGray = 0xFFCCCCCC;
const Color kColorWhite = 0xFFFFFFFF;

const Color kColorRed = 0xFFFF0000;
const Color kColorGreen = 0xFF00FF00;
const Color kColorBlue = 0xFF0000FF;
const Color kColorYellow = 0xFFFFFF00;
const Color kColorCyan = 0xFF00FFFF;
const Color kColorMagenta = 0xFFFF00FF;

inline Color GetA(Color color) { return (color >> 24) & 0xFF; }
inline Color GetR(Color color) { return (color >> 16) & 0xFF; }
inline Color GetG(Color color) { return (color >> 8) & 0xFF; }
inline Color GetB(Color color) { return (color >> 0) & 0xFF; }

inline Color SetARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
  return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

inline Color SetColorCoverage(Color color, int coverage)
{
  Color a = coverage * GetA(color) / 255;
  Color r = coverage * GetR(color) / 255;
  Color g = coverage * GetG(color) / 255;
  Color b = coverage * GetB(color) / 255;
  return SetARGB(a,r,g,b);
}


}

#endif /* LE_COLOR_H_ */


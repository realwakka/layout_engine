#include "bitmap_canvas.h"

#include <cmath>
#include <cstring>
#include <fstream>
#include "model/glyph/glyph.h"
#include "graphic/paint.h"

namespace le {

namespace {

void SetPixel(const Point& p, int brightness, Canvas& canvas)
{
  auto color = SetARGB(0xFF, brightness, brightness, brightness);
  color = kColorBlack;
  canvas.SetPixel(p, color);
}

void DrawLineBresenham(int x0, int y0, int x1, int y1, Canvas& canvas)
{
  int addx,addy;
  int counter = 0;

  int dx = x1 - x0;
  int dy = y1 - y0;

  if ( dx < 0 ) {
    addx = -1;
    dx = -dx;
  } else {
    addx = 1;
  }

  if ( dy < 0 ) {
    addy = -1;
    dy = -dy;
  } else {
    addy = 1;
  }
  
  int x = x0;
  int y = y0;

  if ( dx >= dy ) {
    for (int i = 0; i < dx; ++i ) {
      x += addx;
      counter += dy;
      if( counter >= dx ) {
        y += addy;
        counter -= dx;
      }
      SetPixel(Point(x,y), 0, canvas);
    }
  } else {
    for (int i = 0; i < dy; ++i ) {
      y += addy;
      counter += dx;
      if( counter >= dy ) {
        x += addx;
        counter -= dy;
      }
      SetPixel(Point(x,y), 0, canvas);
    }
  }
}

void DrawLineXiaolinWu(int x0, int y0, int x1, int y1, Canvas& canvas)
{
  bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if( steep ) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if( x0 > x1 ) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  auto dx = x1 - x0;
  auto dy = y1 - y0;
  auto gradient = dy / (float)dx;

  auto xend = std::round(x0);
  auto yend = y1 + gradient * (xend - x0);
  auto tmp = 0.0f;
  auto xgap = std::modf(x0 + 0.5f, &tmp);
  auto xpxl1 = xend;
  auto ypxl1 = 0.0f;

  auto ipart_yend = 0.0f;
  auto rpart_yend = std::modf(yend, &ipart_yend);

  ypxl1 = ipart_yend;
  
  if( steep ) {
    SetPixel( Point(ypxl1, xpxl1), 1 - rpart_yend * xgap * 255, canvas );
    SetPixel( Point(ypxl1 + 1, xpxl1), rpart_yend * xgap * 255, canvas );
  } else {
    SetPixel( Point(xpxl1, ypxl1), 1 - rpart_yend * xgap * 255, canvas );
    SetPixel( Point(xpxl1, ypxl1 + 1), rpart_yend * xgap * 255, canvas );
  }

  auto intery = yend + gradient;

  xend = std::round(x1);
  yend = y1 + gradient * (xend - x1);
  std::modf(x1 + 0.5, &xgap);
  auto xpxl2 = xend;
  auto ypxl2 = 0.0f;
  auto fpart_yend = std::modf(yend, &ypxl2);
  if( steep ) {
    SetPixel(Point(ypxl2, xpxl2), 1 - fpart_yend * xgap * 255, canvas);
    SetPixel(Point(ypxl2 + 1, xpxl2), fpart_yend * xgap * 255, canvas);
  } else {
    SetPixel(Point(xpxl2, ypxl2), 1 - fpart_yend * xgap * 255, canvas);
    SetPixel(Point(xpxl2, ypxl2 + 1), fpart_yend * xgap * 255, canvas);
  }

  if( steep ) {
    for ( int x = xpxl1 + 1 ; x <= xpxl2 - 1 ; ++x ) {
      auto ipart_intery = 0.0f;
      auto fpart_intery = std::modf(intery, &ipart_intery);
      SetPixel(Point(ipart_intery, x), 1 - fpart_intery * 255, canvas);
      SetPixel(Point(ipart_intery + 1, x), fpart_intery * 255, canvas);
      intery = intery + gradient;
    }
  } else {
    for ( int x = xpxl1 + 1 ; x <= xpxl2 - 1 ; ++x ) {
      auto ipart_intery = 0.0f;
      auto fpart_intery = std::modf(intery, &ipart_intery);
      SetPixel(Point(x, ipart_intery), 1 - fpart_intery * 255, canvas);
      SetPixel(Point(x, ipart_intery + 1), fpart_intery * 255, canvas);
      intery = intery + gradient;
    }
  }
}

}


const int kWidth = 500;
const int kHeight = 500;

BitmapCanvas::BitmapCanvas()
{
  
}

BitmapCanvas::~BitmapCanvas()
{
}

void BitmapCanvas::DrawGlyph(const Point& point, const Glyph& glyph)
{
  auto x = point.GetX();
  auto y = point.GetY();

  auto spanlist = glyph.GetSpanList();
  if( spanlist.empty() )
    return;
  
  auto height = spanlist.back().GetY();

  for( auto&& span : spanlist ) {
    //auto color = SetColorCoverage(glyph.GetColor(), span.GetCoverage());

    auto tmp = span.GetCoverage();
    auto color = SetARGB(tmp, 255, 0, 0);
    
    for( int i=0 ; i<span.GetLength() ; ++i ) {
      SetPixel(Point(span.GetX() + x + i, (y - span.GetY())), color);
    }
  }
}

void BitmapCanvas::DrawRect(const Point& p1, const Point& p2, const Paint& paint)
{
  if( paint.GetStyle() == Paint::Style::kFill ) {
    for( auto x = p1.GetX() ; x < p2.GetX() ; x++ ) {
      for( auto y = p1.GetY() ; y < p2.GetY() ; y++ ) {
        SetPixel(Point(x,y), paint.GetColor());
      }
    }
  } else if( paint.GetStyle() == Paint::Style::kStroke ) {
    DrawLine(p1, Point(p1.GetX(), p2.GetY()), paint);
    DrawLine(Point(p1.GetX(), p2.GetY()), p2, paint);
    DrawLine(p2, Point(p2.GetX(), p1.GetY()), paint);
    DrawLine(Point(p2.GetX(), p1.GetY()), p1, paint);
  }
}

void BitmapCanvas::SetPixel(const Point& point, int color)
{
  auto transformed = point.Transform(GetMatrix());
  bitmap_->SetPixel(transformed.GetX(), transformed.GetY(), color);
}

void BitmapCanvas::WriteBitmap(const std::string filename)
{
  bitmap_->WriteBitmapFile(filename);
}

void BitmapCanvas::DrawLine(const Point& p1, const Point& p2, const Paint& paint)
{
  DrawLineBresenham(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY(), *this);
}

}  // le

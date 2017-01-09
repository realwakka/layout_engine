#include "canvas.h"

#include <cmath>
#include <cstring>
#include <fstream>
#include "model/glyph/glyph.h"

namespace le {

namespace {

void DrawLineXiaolinWu(int x0, int y0, int x1, int y1, Canvas& canvas)
{
  // boolean steep := abs(y1 - y0) > abs(x1 - x0)

  //                      if steep then
  //                                   swap(x0, y0)
  //                                   swap(x1, y1)
  //                                       end if
  //                                       if x0 > x1 then
  //                                                   swap(x0, x1)
  //                                                   swap(y0, y1)
  //                                                       end if

  //                                                   dx := x1 - x0
  //                                                             dy := y1 - y0
  //                                                             gradient := dy / dx
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

  auto xend = std::round(x1);
  auto yend = y1 + gradient * (xend - x1);
  auto tmp = 0.0f;
  auto xgap = std::modf(x1 + 0.5f, &tmp);
  auto xpxl2 = xend;
  auto ypxl2 = 0.0f;

  auto ipart_yend = 0.0f;
  auto rpart_yend = std::modf(yend, &ipart_yend);

  ypxl2 = ipart_yend;
  
  if( steep ) {
    canvas.SetPixel( Point(ypxl2, xpxl2), 1 - rpart_yend * xgap * 255 );
    canvas.SetPixel( Point(ypxl2 + 1, xpxl2), rpart_yend * xgap * 255 );
  } else {
    canvas.SetPixel( Point(xpxl2, ypxl2), 1 - rpart_yend * xgap * 255 );
    canvas.SetPixel( Point(xpxl2, ypxl2 + 1), rpart_yend * xgap * 255 );
  }

  auto intery = yend + gradient;

  xend = std::round(x1);
  yend = y1 + gradient * (xend - x1);
  std::modf(x1 + 0.5, &xgap);
  xpxl1 = xend;
  auto fpart_yend = std::modf(yend, &ypxl2);
  if( steep ) {
    canvas.SetPixel(Point(ypxl2, xpxl2), 1 - fpart_yend * xgap * 255);
    canvas.SetPixel(Point(ypxl2 + 1, xpxl2), fpart_yend * xgap * 255);
  } else {
    canvas.SetPixel(Point(xpxl2, ypxl2), 1 - fpart_yend * xgap * 255);
    canvas.SetPixel(Point(xpxl2, ypxl2 + 1), fpart_yend * xgap * 255);
  }

  if( steep ) {
    for ( int x = xpxl1 + 1 ; x <= xpxl2 - 1 ; ++x ) {
      auto ipart_intery = 0;
      auto fpart_intery = std::modf(intery, ipart_intery);
      canvas.SetPixel(ipart_intery, x, 1 - fpart_intery);
      canvas.SetPixel(ipart_intery + 1, x, fpart_intery);
      intery = intery + gradient;
    }
  } else {
    for ( int x = xpxl1 + 1 ; x <= xpxl2 - 1 ; ++x ) {
      auto ipart_intery = 0;
      auto fpart_intery = std::modf(intery, ipart_intery);
      canvas.SetPixel(x, ipart_intery, 1 - fpart_intery);
      canvas.SetPixel(x, ipart_intery + 1, fpart_intery);
      intery = intery + gradient;
    }
  }
                                                                               
  
}

}


const int kWidth = 500;
const int kHeight = 500;

Canvas::Canvas()
    : bitmap_( kWidth, kHeight, 3 )
{
  matrix_stack_.push(Matrix());
}

Canvas::~Canvas()
{
}

void Canvas::DrawGlyph(const Point& point, const Glyph& glyph)
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

void Canvas::DrawRect(const Point& p1, const Point& p2, Color color)
{
  auto x = p1.GetX();
  auto y = p1.GetY();

  for( auto x = p1.GetX() ; x < p2.GetX() ; x++ ) {
    for( auto y = p1.GetY() ; y < p2.GetY() ; y++ ) {
      SetPixel(Point(x,y), color);
    }
  }
}

void Canvas::Save()
{
  matrix_stack_.push(matrix_stack_.top());
}
void Canvas::Restore()
{
  matrix_stack_.pop();
}

void Canvas::SetPixel(const Point& point, int color)
{
  auto transformed = point.Transform(GetMatrix());
  bitmap_.SetPixel(transformed.GetX(), transformed.GetY(), color);
}

void Canvas::WriteBitmap(const std::string filename)
{
  bitmap_.WriteBitmapFile(filename);
}

void Canvas::DrawLine(const Point& p1, const Point& p2)
{
  // boolean steep := abs(y1 - y0) > abs(x1 - x0)

  //                  if steep then
  //                               swap(x0, y0)
  //                               swap(x1, y1)
  //                               end if
  //                               if x0 > x1 then
  //                                           swap(x0, x1)
  //                                           swap(y0, y1)
  //                                           end if

  //                                           dx := x1 - x0
  //                                                     dy := y1 - y0
  //                                                     gradient := dy / dx
                                                              
}

}  // le

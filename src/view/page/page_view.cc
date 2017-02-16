#include "page_view.h"

#include "model/prop/section_prop.h"
#include "view/page/column_view.h"

namespace le {

PageView::PageView(SectionProp& section_prop)
    : section_prop_(section_prop)
{
  auto&& size = section_prop_.GetPageSize();
  SetWidth(conv_util::Twip2Pixel(size.GetWidth()));
  SetHeight(conv_util::Twip2Pixel(size.GetHeight()));
}

PageView::~PageView()
{

}

void PageView::Layout()
{
  view_util::LayoutChilds(this);
}

void PageView::Paint(Canvas& canvas)
{
  view_util::PaintChilds(canvas, this);
}


}  // le

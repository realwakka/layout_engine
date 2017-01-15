#ifndef LE_SECTION_PROP_H_
#define LE_SECTION_PROP_H_

namespace le {

class PageMargin
{
 public:
  PageMargin();
  ~PageMargin();
  
  int GetTop() const { return top_; }
  void SetTop(int top) { top_ = top; }

  int GetRight() const { return right_; }
  void SetRight(int right) { right_ = right; }

  int GetBottom() const { return bottom_; }
  void SetBottom(int bottom) { bottom_ = bottom; }

  int GetLeft() const { return left_; }
  void SetLeft(int left) { left_ = left; }

  int GetHeader() const { return header_; }
  void SetHeader(int header) { header_ = header; }

  int GetFooter() const { return footer_; }
  void SetFooter(int footer) { footer_ = footer; }

  int GetGutter() const { return gutter_; }
  void SetGutter(int gutter) { gutter_ = gutter; }

 private:
  int top_;
  int right_;
  int bottom_;
  int left_;
  int header_;
  int footer_;
  int gutter_;
};

class PageSize
{
 public:
  PageSize();
  virtual ~PageSize();
  
  int GetWidth() const { return width_; }
  void SetWidth(int width) { width_ = width; }

  int GetHeight() const { return height_; }
  void SetHeight(int height) { height_ = height; }

 private:
  int width_;
  int height_;
};

class SectionProp
{
 public:
  SectionProp();
  virtual ~SectionProp();

  const PageSize& GetPageSize() const { return page_size_; }
  const PageMargin& GetPageMargin() const { return page_margin_; }

 private:
  PageSize page_size_;
  PageMargin page_margin_;
  
};


}  // le

#endif /* LE_SECTION_PROP_H_ */

#ifndef LE_DOCUMENT_VIEW_H_
#define LE_DOCUMENT_VIEW_H_

#include <memory>
#include "view/view.h"
#include "view/layer.h"

namespace le {

class Document;
class Layer;

class DocumentView : public View
{
 public:
  DocumentView(Document& document);
  virtual ~DocumentView();

  virtual void Layout();
  virtual void Paint(Canvas& canvas);
  
  void createPageViews();
  
  Document& GetDocument() { return document_; }
  virtual Layer* GetLayer() { return layer_.get(); }

 private:
  Document& document_;
  std::unique_ptr<Layer> layer_;
};


}  // le

#endif /* LE_DOCUMENT_VIEW_H_ */

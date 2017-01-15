#ifndef LE_DOCUMENT_VIEW_H_
#define LE_DOCUMENT_VIEW_H_

#include "view/view.h"

namespace le {

class Document;

class DocumentView : public View
{
 public:
  DocumentView(Document& document);
  virtual ~DocumentView();

  virtual void Layout();
  virtual void Paint(Canvas& canvas);
  
  void createPageViews();
  
  Document& GetDocument() { return document_; }

 private:
  Document& document_;
  
};


}  // le

#endif /* LE_DOCUMENT_VIEW_H_ */

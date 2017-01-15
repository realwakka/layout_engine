#ifndef LE_DOCUMENT_H_
#define LE_DOCUMENT_H_

#include <vector>
#include "model/prop/section_prop.h"
#include "view/document_view.h"
#include "type/container.h"
#include "model/paragraph.h"

namespace le {

class Document
{
 public:
  Document();
  virtual ~Document();

  SectionProp& GetSectionProp() { return section_prop_; }
  DocumentView& GetView() { return view_; }

  Paragraph* GetFirstChild() { return parent_.GetFirstChild(); }
  Paragraph* GetLastChild() { return parent_.GetLastChild(); }
  Paragraph* GetChildAt(int index) const { return parent_.GetChildAt(index); }
  int GetChildCount() const { return parent_.GetChildCount(); }
  void AddChildAt(int index, Paragraph* child) { parent_.AddChildAt(index, child, this); }
  void AppendChild(Paragraph* child) { parent_.AppendChild(child, this); }
  

 private:
  SectionProp section_prop_;
  DocumentView view_;
  Parent<Document, Paragraph> parent_;
};


}  // le

#endif /* LE_DOCUMENT_H_ */

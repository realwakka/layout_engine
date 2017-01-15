#ifndef LE_DOCUMENT_H_
#define LE_DOCUMENT_H_

#include <vector>
#include "model/prop/section_prop.h"
#include "view/document_view.h"

namespace le {

class Paragraph;

class Document
{
 public:
  Document();
  virtual ~Document();

  SectionProp& GetSectionProp() { return section_prop_; }
  DocumentView& GetView() { return view_; }

 private:
  SectionProp section_prop_;
  std::vector<Paragraph*> block_list_;
  DocumentView view_;
};


}  // le

#endif /* LE_DOCUMENT_H_ */

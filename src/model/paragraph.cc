#include "paragraph.h"

#include <algorithm>

namespace le {

Paragraph::Paragraph()
    : enter_run_(this)
{}

Paragraph::~Paragraph()
{}

void Paragraph::InsertRun(Run* new_run, Run* ref_run)
{
  if( ref_run == nullptr )
    runs_.Append(new_run);
  else
    runs_.InsertBefore(new_run, ref_run->GetIterator());

}
void Paragraph::InsertWord(Word* new_word, Word* ref_word)
{
  if( ref_word == nullptr )
    words_.Append(new_word);
  else
    words_.InsertBefore(new_word, ref_word->GetIterator());
}



}  // le

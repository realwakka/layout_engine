#include "paragraph_prop.h"

#include "view/linebreaker/word_linebreaker.h"

namespace le {

ParagraphProp::ParagraphProp()
    : linebreaker_(new WordLineBreaker())
{}
ParagraphProp::~ParagraphProp()
{}

}  // le

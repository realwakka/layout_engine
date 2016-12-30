#include "normal_word_view_delegate.h"

namespace le {

NormalWordViewDelegate::NormalWordViewDelegate(WordView& word_view)
    : WordViewDelegate(word_view)
{}

NormalWordViewDelegate::~NormalWordViewDelegate()
{}

void NormalWordViewDelegate::Layout()
{}

void NormalWordViewDelegate::Paint(Canvas& canvas)
{}

}  // le



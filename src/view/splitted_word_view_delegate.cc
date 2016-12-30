#include "splitted_word_view_delegate.h"

namespace le {

SplittedWordViewDelegate::SplittedWordViewDelegate(WordView& word_view)
    : WordViewDelegate(word_view)
{}

SplittedWordViewDelegate::~SplittedWordViewDelegate()
{}

void SplittedWordViewDelegate::Layout()
{}

void SplittedWordViewDelegate::Paint(Canvas& canvas)
{}

}  // le



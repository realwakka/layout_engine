#include "word_linebreaker.h"

#include "model/paragraph.h"

#include "view/line_view.h"

#include <vector>

namespace le {

namespace {

void InsertCharacters(std::vector<Character*>& line, Word* word)
{
  for(auto c = word->GetFirstCharacter() ; c ; c = c->GetNextWordCharacter() ) {
    line.push_back(c);
  }
}

}

WordLineBreaker::WordLineBreaker()
{}

WordLineBreaker::~WordLineBreaker()
{}
  
void WordLineBreaker::BreakLine(Paragraph& paragraph)
{
  auto& paragraph_view = paragraph.GetView();

  auto linewidth = paragraph_view.GetWidth();

  std::vector<std::vector<Character*>> lines;
  lines.push_back(std::vector<Character*>());

  auto spaceleft = linewidth;

  for( auto word = paragraph.GetFirstWord() ; word ; word = word->GetNextWord() ) {
    auto wordwidth = word->GetWordWidth();
    auto spacewidth = word->GetSpaceWidth();

    if( wordwidth > linewidth ) {
      //split
    } else if( wordwidth - spacewidth > spaceleft ) {
      //go to newline
      lines.push_back(std::vector<Character*>());
      InsertCharacters(lines.back(), word);
    } else {
      //push to current line
      InsertCharacters(lines.back(), word);
      spaceleft -= wordwidth;
    }
  }
}


}  // le

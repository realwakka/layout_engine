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

void createViews(std::vector<std::vector<Character*>>& lines, ParagraphView& paragraph_view )
{
  while( paragraph_view.GetFirstChild() )
    paragraph_view.RemoveChildAt(0);
  for(auto line : lines ) {
    auto lineview = new LineView();
    for(auto character : line ) {
      auto& characterview = character->GetView();
      auto runview = static_cast<RunView*>(lineview->GetLastChild());
      auto run = character->GetRun();
      
      if( runview && &runview->GetRun() == run ) {
        lineview->GetLastChild()->AppendChild(&characterview);
      } else {
        lineview->AppendChild(new RunView(*run));
        lineview->GetLastChild()->AppendChild(&characterview);
      }
    }
    paragraph_view.AppendChild(lineview);
  }

  auto enter_char = paragraph_view.GetParagraph().GetEnterRun()->GetEnterChar();
  paragraph_view.GetLastChild()->AppendChild(&enter_char->GetView());
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

    if( wordwidth - spacewidth > spaceleft ) {
      if( lines.back().empty() ) {
        //split!
        auto remain = 0;
        auto splitted_words = word->GetSplittedWord(spaceleft, remain);

        for( auto&& splitted_word : splitted_words ) {
          for( auto&& splitted_chars : splitted_word ) {
            lines.back().push_back(splitted_chars);
          }
          lines.push_back(std::vector<Character*>());
        }
        
        spaceleft = linewidth - remain;
      } else {
        //go to newline
        lines.push_back(std::vector<Character*>());
        InsertCharacters(lines.back(), word);
        spaceleft = linewidth - wordwidth;
      }
      
    } else {
      //push to current line
      InsertCharacters(lines.back(), word);
      spaceleft -= wordwidth;
    }
  }

  createViews(lines, paragraph_view);
}


}  // le

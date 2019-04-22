#include "highlighter.h"

#include <fstream>

namespace 
{
    std::wstring prefix(L"<i class=\"src\">");
    std::wstring suffix(L"</i>");
}

Highlighter::Highlighter(
    const TrieNodePtr& dictionary,
    TokenizerPtr tokenizer) :
    dictionary_(dictionary),
    tokenizer_(tokenizer)
{
}

void Highlighter::highlight(std::wostream& ostream) const
{
    std::wstring word;
    while (tokenizer_->get_next_token(word))
    {
        if (tokenizer_->current_token_is_highlightable() && 
            dictionary_->contains(word))
        {
            ostream << prefix << word << suffix;
        }
        else
        {
            ostream << word;
        }
    }
    ostream.flush();
}

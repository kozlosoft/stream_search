#include "plain_tokenizer.h"

#include <sstream>

PlainTokenizer::PlainTokenizer(std::wistream& stream):
    stream_(stream),
    current_delimeter_()
{
}

bool PlainTokenizer::get_next_token(std::wstring& word)
{
    word = L"";
    if (! current_delimeter_.empty())
    {
        word = current_delimeter_;
        current_delimeter_ = L"";
        return true;
    }

    std::wstringstream ss;
    wchar_t symbol;
    while (! stream_.eof())
    {
        if (stream_.get(symbol))
        {
            if (std::iswalnum(symbol))
            {
                ss << symbol;
            }
            else
            {
                word = ss.str();
                if (word.empty())
                {
                    word = symbol;
                }
                else
                {
                    current_delimeter_ = symbol;
                }
                return true;
            }
        }
        else
        {
            word = ss.str();
            return ! word.empty();
        }
    }
    return false;
}

bool PlainTokenizer::current_token_is_highlightable() const {
    return true;
}
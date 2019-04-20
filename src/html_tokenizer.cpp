#include "html_tokenizer.h"

HtmlTokenizer::HtmlTokenizer(std::wistream& stream) :
    plain_tokenizer_(stream),
    is_inside_tag_(false),
    is_tag_closed_(false)
{
}

bool HtmlTokenizer::get_next_token(std::wstring& word) 
{
    bool answer = plain_tokenizer_.get_next_token(word);
    
    if (word == L"<") {
        is_inside_tag_ = true;
    } else if (word == L">") {
        is_tag_closed_ = true;
    }
    else
    {
       if (is_tag_closed_ && is_inside_tag_) 
       {
           is_tag_closed_ = false;
           is_inside_tag_ = false;
       }
    }
    
    return answer;
}

bool HtmlTokenizer::current_token_is_highlightable() const 
{
    return 
        ! is_inside_tag_;
}
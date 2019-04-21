#include "html_tokenizer.h"

HtmlTokenizer::HtmlTokenizer(std::wistream& stream) :
    plain_tokenizer_(stream),
    is_inside_tag_(false),
    is_tag_closed_(false),
    next_token_after_open_angle_bracket_(),
    next_token_after_open_angle_bracket_stream_status_(false)
{
}

bool HtmlTokenizer::get_next_token(std::wstring& word) 
{
    bool answer = false;
    if (! next_token_after_open_angle_bracket_.empty())
    {
        word = next_token_after_open_angle_bracket_;
        answer = next_token_after_open_angle_bracket_stream_status_;

        next_token_after_open_angle_bracket_ = L"";
        next_token_after_open_angle_bracket_stream_status_ = false;
        
    }
    else
    {
        answer = plain_tokenizer_.get_next_token(word);
    }
    
    if (word == L"<") {
        is_inside_tag_ = true;
        is_tag_closed_ = false;

        next_token_after_open_angle_bracket_stream_status_ =
            plain_tokenizer_.get_next_token(
                next_token_after_open_angle_bracket_);
        if (next_token_after_open_angle_bracket_stream_status_)
        {
            bool next_is_alpha = std::iswalpha(
                next_token_after_open_angle_bracket_[0]);
            if (! next_is_alpha &&
                next_token_after_open_angle_bracket_ != L"/")
            {
                is_inside_tag_ = false;
                is_tag_closed_ = false;
            }
        }
    } else if (word == L">") {
        is_tag_closed_ = true;
    }
    else // not "<" and not ">"
    {
       if (is_tag_closed_ && is_inside_tag_) 
       {
           is_inside_tag_ = false;
           is_tag_closed_ = false;
       }
    }
    
    return answer;
}

bool HtmlTokenizer::current_token_is_highlightable() const 
{
    return 
        ! is_inside_tag_;
}
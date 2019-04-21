#include "html_tokenizer.h"

HtmlTokenizer::HtmlTokenizer(std::wistream& stream) :
    plain_tokenizer_(stream),
    is_inside_tag_(false),
    is_tag_closed_(false),
    is_inside_closing_tag_(false),
    next_token_after_open_angle_bracket_(),
    next_token_after_open_angle_bracket_stream_status_(false),
    is_inside_script_(false),
    is_inside_style_(false)
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
    
    handle_angle_brackets(word);
    handle_script_tag(word);
    handle_style_tag(word);
    
    return answer;
}

void HtmlTokenizer::handle_angle_brackets(const std::wstring& word)
{
    if (word == L"<") {
        is_inside_tag_ = true;
        is_tag_closed_ = false;
        is_inside_closing_tag_ = false;

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
            if (next_token_after_open_angle_bracket_ == L"/")
            {
                is_inside_closing_tag_ = true;
            }
        }
    } else if (word == L">") {
        is_tag_closed_ = true;
        is_inside_closing_tag_ = false;
    }
    else // not "<" and not ">"
    {
       if (is_tag_closed_ && is_inside_tag_) 
       {
           is_inside_tag_ = false;
           is_tag_closed_ = false;
       }
    }
}

void HtmlTokenizer::handle_script_tag(const std::wstring& word)
{
    if (next_token_after_open_angle_bracket_ == L"script")
    {
        is_inside_script_ = true;
    }
    if (is_inside_closing_tag_ && word == L"script")
    {
        is_inside_script_ = false;
    }
}

void HtmlTokenizer::handle_style_tag(const std::wstring& word)
{
    if (next_token_after_open_angle_bracket_ == L"style")
    {
        is_inside_style_ = true;
    }
    if (is_inside_closing_tag_ && word == L"style")
    {
        is_inside_style_ = false;
    }
}

bool HtmlTokenizer::current_token_is_highlightable() const 
{
    return 
        ! is_inside_tag_ && 
        ! is_inside_script_ &&
        ! is_inside_style_;
}

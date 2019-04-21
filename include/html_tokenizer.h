#pragma once

#include "plain_tokenizer.h"

#include <istream>

class HtmlTokenizer final : public AbstractTokenizer
{
public:
    HtmlTokenizer(std::wistream& stream);
    HtmlTokenizer(const HtmlTokenizer&) = delete;
    HtmlTokenizer(HtmlTokenizer&&) = delete;
    HtmlTokenizer& operator=(const HtmlTokenizer&) = delete;
    HtmlTokenizer& operator=(HtmlTokenizer&&) = delete;
    ~HtmlTokenizer() = default;

    bool get_next_token(std::wstring& word) override;
    bool current_token_is_highlightable() const override;

private:
    void hadle_angle_brackets(const std::wstring& word);

private:
    PlainTokenizer plain_tokenizer_;

    bool is_inside_tag_;
    bool is_tag_closed_;
    std::wstring next_token_after_open_angle_bracket_;
    bool next_token_after_open_angle_bracket_stream_status_;

    bool is_inside_script_;
    bool is_inside_style_;
};

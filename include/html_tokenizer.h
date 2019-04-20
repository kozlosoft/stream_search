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
    PlainTokenizer plain_tokenizer_;

    bool is_inside_tag_;
    bool is_tag_closed_;
};

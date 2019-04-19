#pragma once

#include "abstract_tokenizer.h"

#include <istream>

class PlainTokenizer final : public AbstractTokenizer
{
public:
    PlainTokenizer(std::wistream& stream);
    PlainTokenizer(const PlainTokenizer&) = delete;
    PlainTokenizer(PlainTokenizer&&) = delete;
    PlainTokenizer& operator=(const PlainTokenizer&) = delete;
    PlainTokenizer& operator=(PlainTokenizer&&) = delete;
    ~PlainTokenizer() = default;

    bool get_next_token(std::wstring& word) override;
    bool current_token_is_highlightable() const override;

private:
    std::wistream& stream_;
    std::wstring current_delimeter_;
};

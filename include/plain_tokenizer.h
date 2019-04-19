#pragma once

#include <istream>

class PlainTokenizer
{
public:
    PlainTokenizer(std::wistream& stream);
    PlainTokenizer(const PlainTokenizer&) = delete;
    PlainTokenizer(PlainTokenizer&&) = delete;
    PlainTokenizer& operator=(const PlainTokenizer&) = delete;
    PlainTokenizer& operator=(PlainTokenizer&&) = delete;
    ~PlainTokenizer() = default;

    bool get_next_token(std::wstring& word);

private:
    std::wistream& stream_;
    std::wstring current_delimeter_;
};

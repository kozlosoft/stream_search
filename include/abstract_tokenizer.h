#pragma once

#include <string>
#include <memory>

class AbstractTokenizer
{
public:
    virtual ~AbstractTokenizer() = default;

    virtual bool get_next_token(std::wstring& word) = 0;
    virtual bool current_token_is_highlightable() const = 0;
};
typedef std::shared_ptr<AbstractTokenizer> TokenizerPtr;

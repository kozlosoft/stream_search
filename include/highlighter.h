#pragma once

#include "trie.h"
#include "abstract_tokenizer.h"

class Highlighter
{
public:
    Highlighter(
        const TrieNodePtr& dictionary,
        TokenizerPtr tokenizer);
    Highlighter(const Highlighter&) = delete;
    Highlighter(Highlighter&&) = delete;
    Highlighter& operator=(const Highlighter&) = delete;
    Highlighter& operator=(Highlighter&&) = delete;
    ~Highlighter() = default;

    void highlight(std::wostream& ostream) const;

private:
    TrieNodePtr dictionary_;
    TokenizerPtr tokenizer_;
};

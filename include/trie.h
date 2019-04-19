#pragma once

#include <unordered_map>
#include <memory>

class TrieNode
{
public:
    TrieNode() :
        children_(),
        end_of_word_(false)
    {
    }
    TrieNode(const TrieNode&) = delete;
    TrieNode(TrieNode&&) = delete;
    TrieNode& operator=(const TrieNode&) = delete;
    TrieNode& operator=(TrieNode&&) = delete;
    ~TrieNode() = default;

    void insert(const std::wstring& word, size_t char_index = 0);
    bool contains(const std::wstring& word, size_t char_index = 0) const;
    void read_file_stream(std::wistream& stream);

public:
    std::unordered_map<wchar_t, std::shared_ptr<TrieNode> > children_;
    bool end_of_word_;
};
typedef std::shared_ptr<TrieNode> TrieNodePtr;

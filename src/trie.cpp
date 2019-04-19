#include "trie.h"

void TrieNode::insert(const std::wstring& word, size_t char_index)
{
    if (char_index >= word.size()) 
    {
        end_of_word_ = true;
        return;
    }

    TrieNodePtr& child_ptr = children_[word[char_index]];
    if (child_ptr == nullptr) 
    {
        child_ptr = std::make_shared<TrieNode>();
    }
    child_ptr->insert(word, char_index + 1);
}

bool TrieNode::contains(const std::wstring& word, size_t char_index) const
{
    if (char_index >= word.size()) 
    {
        return end_of_word_;
    }

    auto it = children_.find(word[char_index]);
    if (it == children_.end())
    {
        return false;
    }
    return it->second->contains(word, char_index + 1);
}

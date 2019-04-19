#include "trie.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(Trie, InitWithUnicodeLines)
{
    // arrange
    std::vector<std::wstring> lines = {
        L"аб ",
        L"ав",
    };
    TrieNode root;

    // action
    for (const auto& line : lines)
        root.insert(line);

    // assert
    ASSERT_EQ(root.children_.size(), 1);
    ASSERT_EQ(root.end_of_word_, false);

    TrieNodePtr a_node = root.children_[L'а'];
    ASSERT_EQ(a_node->children_.size(), 2);
    ASSERT_EQ(a_node->end_of_word_, false);

    TrieNodePtr b_node = a_node->children_[L'б'];
    ASSERT_EQ(b_node->children_.size(), 1);
    ASSERT_EQ(b_node->end_of_word_, false);

    TrieNodePtr space_node = b_node->children_[L' '];
    ASSERT_EQ(space_node->children_.size(), 0);
    ASSERT_EQ(space_node->end_of_word_, true);

    TrieNodePtr v_node = a_node->children_[L'в'];
    ASSERT_EQ(v_node->children_.size(), 0);
    ASSERT_EQ(v_node->end_of_word_, true);
}

TEST(Trie, Contains)
{
    // arrange
    std::vector<std::wstring> lines = {
        L"аб ",
        L"ав",
    };
    TrieNode root;
    for (const auto& line : lines)
        root.insert(line);

    // action
    // assert
    ASSERT_EQ(root.contains(L"аб "), true);
    ASSERT_EQ(root.contains(L"ав"), true);
    
    ASSERT_EQ(root.contains(L"а"), false);
    ASSERT_EQ(root.contains(L" "), false);
    ASSERT_EQ(root.contains(L"аб"), false);
    ASSERT_EQ(root.contains(L""), false);
}

TEST(Trie, ContainsEmptyString)
{
    // arrange
    TrieNode root;
    root.insert(L"");

    // action
    // assert
    ASSERT_EQ(root.contains(L""), true);
}

TEST(Trie, ReadFileStream)
{
    // arrange
    std::wstringstream ss;
    std::wstring first_line(L"asd asd первая строка");
    std::wstring second_line(L"последняя строка");
    ss << first_line << std::endl;
    ss << second_line;
    TrieNode root;

    // action
    root.read_file_stream(ss);

    // assert
    ASSERT_EQ(root.contains(first_line), true);
    ASSERT_EQ(root.contains(second_line), true);

    ASSERT_EQ(root.contains(L"asd"), false);
}

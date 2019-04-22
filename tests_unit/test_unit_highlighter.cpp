#include "highlighter.h"
#include "plain_tokenizer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(HighlighterTest, HighlightBasic)
{
    // arrange
    std::wstringstream istream;
    istream << L"a aaa a";
    std::wstringstream ostream;
    std::wstring expected(L"a <i class=\"src\">aaa</i> a");

    TrieNodePtr dictionary = std::make_shared<TrieNode>();
    dictionary->insert(L"aaa");

    TokenizerPtr tokenizer = 
        std::make_shared<PlainTokenizer>(istream);

    Highlighter highlighter(
        dictionary, 
        tokenizer);

    // action
    highlighter.highlight(ostream);

    // assert
    ASSERT_EQ(ostream.str(), expected);
}

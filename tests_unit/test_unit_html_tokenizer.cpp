#include "html_tokenizer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

typedef std::pair<std::wstring, bool> WordHighlightablePair;

TEST(HtmlTokenizer, GetNextTokenIgnoresTokensInHtmlTags1)
{
    // arrange
    std::wstringstream ss;
    ss << L"<abc>abc</abc>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"abc", false},
        {L">", false},
        {L"abc", true},
        {L"<", false},
        {L"/", false},
        {L"abc", false},
        {L">", false},
    };

    HtmlTokenizer tokenizer(ss);

    // action
    std::wstring word;
    std::vector<WordHighlightablePair> actual;
    while (tokenizer.get_next_token(word))
    {
        actual.push_back(
            std::make_pair(
                word, 
                tokenizer.current_token_is_highlightable()));
    }

    // assert
    ASSERT_EQ(actual, expected);
}

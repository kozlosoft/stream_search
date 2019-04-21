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

TEST(HtmlTokenizer, GetNextTokenHandleOpenAngleBracket1)
{
    // arrange
    std::wstringstream ss;
    ss << L"<p><abc</p>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"p", false},
        {L">", false},
        {L"<", false},
        {L"abc", false},
        {L"<", false},
        {L"/", false},
        {L"p", false},
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

TEST(HtmlTokenizer, GetNextTokenHandleOpenAngleBracket2)
{
    // arrange
    std::wstringstream ss;
    ss << L"<p><abc </p>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"p", false},
        {L">", false},
        {L"<", false},
        {L"abc", false},
        {L" ", false},
        {L"<", false},
        {L"/", false},
        {L"p", false},
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

TEST(HtmlTokenizer, GetNextTokenHandleOpenAngleBracket3)
{
    // arrange
    std::wstringstream ss;
    ss << L"<p>< abc </p>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"p", false},
        {L">", false},
        {L"<", true},
        {L" ", true},
        {L"abc", true},
        {L" ", true},
        {L"<", false},
        {L"/", false},
        {L"p", false},
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

TEST(HtmlTokenizer, GetNextTokenHandleOpenAngleBracket4)
{
    // arrange
    std::wstringstream ss;
    ss << L"<p><</p>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"p", false},
        {L">", false},
        {L"<", true},
        {L"<", false},
        {L"/", false},
        {L"p", false},
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

TEST(HtmlTokenizer, GetNextTokenHandleOpenAngleBracket5)
{
    // arrange
    std::wstringstream ss;
    ss << L"<p><2</p>";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"p", false},
        {L">", false},
        {L"<", true},
        {L"2", true},
        {L"<", false},
        {L"/", false},
        {L"p", false},
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

TEST(HtmlTokenizer, GetNextTokenIgnoresScriptTag1)
{
    // arrange
    std::wstringstream ss;
    ss << L"<script>a</script>b";
    std::vector<WordHighlightablePair> expected = {
        {L"<", false},
        {L"script", false},
        {L">", false},
        {L"a", false},
        {L"<", false},
        {L"/", false},
        {L"script", false},
        {L">", false},
        {L"b", true},
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

TEST(HtmlTokenizer, GetNextTokenIgnoresStyleTag1)
{
    // arrange
    std::wstringstream ss;
    ss << L"c<style>a</style>b";
    std::vector<WordHighlightablePair> expected = {
        {L"c", true},
        {L"<", false},
        {L"style", false},
        {L">", false},
        {L"a", false},
        {L"<", false},
        {L"/", false},
        {L"style", false},
        {L">", false},
        {L"b", true},
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

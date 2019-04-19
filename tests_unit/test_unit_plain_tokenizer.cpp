#include "plain_tokenizer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(PlainTokenizer, GetNextToken)
{
    // arrange
    std::wstringstream ss;
    ss << L"abc абв/абв123 123 ф";
    std::vector<std::wstring> expected_tokens = {
        L"abc",
        L" ",
        L"абв",
        L"/",
        L"абв123",
        L" ",
        L"123",
        L" ",
        L"ф"
    };

    PlainTokenizer tokenizer(ss);

    // action
    std::wstring word;
    std::vector<std::wstring> actual_tokens;
    while (tokenizer.get_next_token(word))
    {
        actual_tokens.push_back(word);
    }

    // assert
    ASSERT_EQ(actual_tokens, expected_tokens);
}

TEST(PlainTokenizer, GetNextTokenEndsWithDelimeter)
{
    // arrange
    std::wstringstream ss;
    ss << L"123 ф ";
    std::vector<std::wstring> expected_tokens = {
        L"123",
        L" ",
        L"ф",
        L" ",
    };

    PlainTokenizer tokenizer(ss);

    // action
    std::wstring word;
    std::vector<std::wstring> actual_tokens;
    while (tokenizer.get_next_token(word))
    {
        actual_tokens.push_back(word);
    }

    // assert
    ASSERT_EQ(actual_tokens, expected_tokens);
}

TEST(PlainTokenizer, GetNextTokenEndsWithLongWord)
{
    // arrange
    std::wstringstream ss;
    ss << L"123 фsd";
    std::vector<std::wstring> expected_tokens = {
        L"123",
        L" ",
        L"фsd",
    };

    PlainTokenizer tokenizer(ss);

    // action
    std::wstring word;
    std::vector<std::wstring> actual_tokens;
    while (tokenizer.get_next_token(word))
    {
        actual_tokens.push_back(word);
    }

    // assert
    ASSERT_EQ(actual_tokens, expected_tokens);
}

TEST(PlainTokenizer, GetNextTokenOnEmpty)
{
    // arrange
    std::wstringstream ss;
    std::vector<std::wstring> expected_tokens;

    PlainTokenizer tokenizer(ss);

    // action
    std::wstring word;
    std::vector<std::wstring> actual_tokens;
    while (tokenizer.get_next_token(word))
    {
        actual_tokens.push_back(word);
    }

    // assert
    ASSERT_EQ(actual_tokens, expected_tokens);
}

TEST(PlainTokenizer, CurrentTokenAlwaysHighlightable)
{
    // arrange
    std::wstringstream ss;
    ss << "hi";

    PlainTokenizer tokenizer(ss);

    // action
    // assert
    ASSERT_EQ(tokenizer.current_token_is_highlightable(), true);
    std::wstring word;
    while (tokenizer.get_next_token(word))
    {
        ASSERT_EQ(tokenizer.current_token_is_highlightable(), true);
    }
    ASSERT_EQ(tokenizer.current_token_is_highlightable(), true);
}

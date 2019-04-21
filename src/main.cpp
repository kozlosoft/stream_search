#include "trie.h"
#include "plain_tokenizer.h"
#include "html_tokenizer.h"
#include "highlighter.h"

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
#ifdef __APPLE__
    // for macosx g++ only
    if (setlocale(LC_ALL, "en_US.UTF-8") == nullptr)
    {
        std::cout << "can't set the locale" << std::endl;
        return -1;
    }
#elif __linux__
    std::ios_base::sync_with_stdio(false);
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    // this also works for macosx clang++,
    //      but not for macosx g++
    std::locale::global(std::locale("en_US.UTF-8"));
#else
    std::cout << "not supported platform" << std::endl;
    return -1;
#endif
    (void) argc;
    
    std::string dictionary_path(argv[1]);
    std::string input_type(argv[2]);

    std::wifstream dictionary_file_stream(dictionary_path);
    TrieNodePtr dictionary = std::make_shared<TrieNode>();
    dictionary->read_file_stream(dictionary_file_stream);

    TokenizerPtr tokenizer;
    if (input_type == "text")
    {
        tokenizer = 
        std::make_shared<PlainTokenizer>(std::wcin);
    }
    else if (input_type == "html")
    {
        tokenizer = 
        std::make_shared<HtmlTokenizer>(std::wcin);
    }
    else
    {
        std::cout << "not supported input type=" << input_type << std::endl;
        return 1;
    }
    
    Highlighter highlighter(
        dictionary, 
        tokenizer);
    highlighter.highlight(std::wcout);

    return 0;
}

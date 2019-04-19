#include "gtest/gtest.h"

#include <locale>

int main(int argc, char **argv)
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
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

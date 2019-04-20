cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project (stream_search)

# we need TMP_LIBRARY here to be able to link binary sources to unit-tests
set(TMP_LIBRARY ${PROJECT_NAME}_lib) 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

enable_testing()

set(${PROJECT_NAME}_SRC_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(${PROJECT_NAME}_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SRC_DIR}/trie.cpp
    ${${PROJECT_NAME}_SRC_DIR}/plain_tokenizer.cpp
    ${${PROJECT_NAME}_SRC_DIR}/highlighter.cpp
    ${${PROJECT_NAME}_SRC_DIR}/html_tokenizer.cpp
    )

set(${PROJECT_NAME}_HEADERS
    ${${PROJECT_NAME}_INCLUDE_DIR}/trie.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/plain_tokenizer.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/abstract_tokenizer.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/highlighter.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/html_tokenizer.h
    )

add_library(${TMP_LIBRARY} STATIC
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})
target_include_directories(${TMP_LIBRARY}
  PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR})
set_target_properties(${TMP_LIBRARY} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)
target_compile_options(${TMP_LIBRARY} PRIVATE -Wall -Wextra -pedantic -Werror -Wfatal-errors)

add_executable(${PROJECT_NAME} 
    ${${PROJECT_NAME}_SRC_DIR}/main.cpp
    )
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${TMP_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Wfatal-errors)

add_subdirectory(tests_unit)

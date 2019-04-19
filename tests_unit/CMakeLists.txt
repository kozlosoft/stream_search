cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(stream_search_unit)

include(ExternalProject)

if (NOT TARGET googletest)
  ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    UPDATE_DISCONNECTED 1
    GIT_SHALLOW 1
    GIT_TAG "release-1.8.1"
    CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=$<CONFIG>
    -Dgtest_force_shared_crt=ON
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest"
    INSTALL_COMMAND ""
    )
endif()

add_executable(${PROJECT_NAME}
  main.cpp
  test_unit_trie.cpp
  test_unit_plain_tokenizer.cpp
  )
add_test(
    NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Wfatal-errors)

ExternalProject_Get_Property(googletest SOURCE_DIR)
set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/googletest/include)
set(GMOCK_INCLUDE_DIRS ${SOURCE_DIR}/googlemock/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS})

add_dependencies(${PROJECT_NAME} googletest)

ExternalProject_Get_Property(googletest BINARY_DIR)
set(GTEST_LIBS_DIR ${BINARY_DIR}/googlemock/gtest)
set(GMOCK_LIBS_DIR ${BINARY_DIR}/googlemock)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  stream_search_lib
  ${GTEST_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
  # ${GTEST_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${GMOCK_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX})
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        pthread 
        )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        # pthread 
        )
endif()
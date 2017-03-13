cmake_minimum_required(VERSION 3.5)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runParserExprTests tests.cpp ${COMPILER_SOURCE_FILES})

target_link_libraries(runParserExprTests gtest gtest_main)
target_link_libraries(runParserExprTests compiler)

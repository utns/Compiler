include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runParserTests tests.cpp ${COMPILER_SOURCE_FILES})

target_link_libraries(runParserTests gtest gtest_main)
target_link_libraries(runParserTests compiler)

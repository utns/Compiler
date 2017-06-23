include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runGeneratorTests tests.cpp ${COMPILER_SOURCE_FILES})

target_link_libraries(runGeneratorTests gtest gtest_main)
target_link_libraries(runGeneratorTests compiler)


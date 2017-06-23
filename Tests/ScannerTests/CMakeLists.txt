include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runScannerTests tests.cpp ${COMPILER_SOURCE_FILES})

target_link_libraries(runScannerTests gtest gtest_main)
target_link_libraries(runScannerTests compiler)

cmake_minimum_required(VERSION 2.8)
project(Compiler)

add_definitions(-std=c++11)

include_directories(Source)
set(SOURCE_FILES main.cpp)
add_executable(Compiler_run ${SOURCE_FILES})

add_subdirectory(Tests)
add_subdirectory(Source)


target_link_libraries(Compiler_run compiler)

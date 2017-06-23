cmake_minimum_required(VERSION 2.8)
project(CompilerTests)

add_subdirectory(lib/googletest)
add_subdirectory(ScannerTests)
add_subdirectory(ParserExprTests)
add_subdirectory(ParserDeclTests)
add_subdirectory(ParserTests)
add_subdirectory(GeneratorTests)


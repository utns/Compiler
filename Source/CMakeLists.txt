project(source)

set(SOURCE_FILES
        errors.cpp
        scanner.cpp
        token.cpp
        parser.cpp
        syntaxnodes.cpp

        errors.h
        scanner.h
        token.h
        parser.h
        syntaxnodes.h)

add_library(compiler STATIC  ${SOURCE_FILES})
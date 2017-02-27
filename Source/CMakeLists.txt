project(source)

set(SOURCE_FILES
        errors.cpp
        scanner.cpp
        token.cpp

        errors.h
        scanner.h
        token.h
)

add_library(compiler STATIC  ${SOURCE_FILES})
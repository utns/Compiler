project(source)

set(SOURCE_FILES
        asmgen.cpp
        errors.cpp
        scanner.cpp
        token.cpp
        parser.cpp
        syntaxnodes.cpp
        symtable.cpp
        symbols.cpp
        optimizer.cpp

        asmgen.h
        errors.h
        scanner.h
        token.h
        parser.h
        syntaxnodes.h
        symbols.h
        optimizer.h
        )

add_library(compiler STATIC ${SOURCE_FILES})
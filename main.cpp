#include <iostream>
#include "scanner.h"
#include "token.h"
#include "errors.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc == 3 && argv[1][0] == '-') {
        if (argv[1][1] == 's') {
            Scanner scanner(argv[2]);
            std::cout << scanner.getTokensString();
        } else if (argv[1][1] == 'p') {
            Parser parser(argv[2]);
            std::cout << parser.getTreeString();
        }
    }
    return 0;
}
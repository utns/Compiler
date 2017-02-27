#include <iostream>
#include "scanner.h"
#include "token.h"
#include "errors.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        Scanner scanner(argv[1]);
        std::cout << scanner.getTokensString();
    }
    return 0;
}
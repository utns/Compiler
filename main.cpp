#include <iostream>
#include <fstream>
#include "scanner.h"
#include "token.h"
#include "errors.h"
#include "parser.h"

//#define NO_SYMBOL_CHECK

int main(int argc, char* argv[]) {
//    if (argc == 3 && argv[1][0] == '-') {
//        if (argv[1][1] == 's') {
//            Scanner scanner(argv[2]);
//            std::cout << scanner.getTokensString();
//        } else if (argv[1][1] == 'p') {
//            Parser parser(argv[2]);
//            std::cout << parser.getTreeString();
//        }
//    }
//    parser.parse();
//    std::cout << parser.getDeclString();
//    std::cout << "____________________" << std::endl;
//    std::cout << parser.getTreeString();
//    std::cout << parser.getDeclTestString() << std::endl;
//    std::cout << "----------------------" << std::endl;
//    std::cout << parser.getRoot()->getString(0) << std::endl;
//    std::cout << "----------------------" << std::endl;
    try {
        Parser parser(argv[1]);
//        std::cout << parser.getDeclTestString() << std::endl;
        parser.getTreeString();
//        std::cout << "----------------------" << std::endl;
//        std::cout << parser.getRoot()->getString(0) << std::endl;
//        std::cout << "----------------------" << std::endl;
        parser.generateAsmCode();
        std::ofstream asmFile;
        asmFile.open(std::string(argv[2]));
        asmFile << parser.getAsmString();
    } catch (BaseError& error) {
        std::cout << error.what() << std::endl;
    }
    return 0;
}
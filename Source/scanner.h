#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <map>
#include "token.h"

class Scanner {
    public:
        Scanner(const char *fileName);
        std::shared_ptr<Token> getNextToken();
        void nextToken();
        std::shared_ptr<Token> getToken();
        std::string getTokenString();
        std::string getTokensString();
    private:
        bool readChar();
        void setToken(Token* token);
        bool isDigit();
        void getNumber();
        void getString();
        void skipComment();
        bool isWhitespace();
        bool isLetter();
        bool isDelimiter();
        void getDelimiter();
        void getOperation();
        void getIdentifier();
        void getBinary();
        bool isOperation();
        void skipSingleLineComment();
        void setIntegerNumber(std::string text, std::string value, int base = 10);
        void setFloatNumber(std::string text);
        std::ifstream fin;
        std::shared_ptr<Token> token;
        std::string text;
        char peek;
        int line;
        int pos;
        int startLine;
        int startPos;
        std::string buffer;
        std::map<std::string, TokenType> delimiters;
        std::map<std::string, TokenType> operations;
        std::map<std::string, TokenType> reservedWords;
};

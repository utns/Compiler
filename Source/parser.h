#pragma once

#include <string>
#include <vector>
#include "scanner.h"
#include "syntaxnodes.h"
#include "token.h"

class Parser {
    public:
        Parser(const char* fileName);
        void parse();
        std::string getTreeString();
    private:
        ExprPtr parseExpr(int priority);
        ExprPtr parseFactor();
        ExprPtr parseIdentifier(TokenPtr token);
        ExprPtr parseArrayAccess(ExprPtr left);
        std::vector<ExprPtr> getArrayIndexes();
        bool checkPriority(int priority, TokenType tokenType);
        bool isUnary(TokenType operation);
        bool checkTokenType(TokenPtr token, TokenType expectedType, std::string expected);
        Scanner scanner;
        std::map<TokenType, int> operationsPriority;
        std::vector<TokenType> unaryOperations;
        ExprPtr root;
        int maxOperationPriority = 3;
};

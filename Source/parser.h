#pragma once

#include <string>
#include <vector>
#include "scanner.h"
#include "syntaxnodes.h"
#include "token.h"
#include "symbols.h"
#include "asmgen.h"

class Parser {
    public:
        Parser(const char* fileName);
        void parse();
        void parseExpr();
        std::string getTreeString();
        std::string getExprTreeString();
        std::string getDeclString();
        std::string getDeclTestString();
        SyntaxNodePtr getRoot();
        std::string getAsmString();
        void generateAsmCode();
    private:
        ExprPtr parseExpr(int priority);
        ExprPtr parseFactor();
        ExprPtr parseIdentifier(TokenPtr token);
        ExprPtr parseArrayAccess(ExprPtr left);
        ExprPtr parseCall(ExprPtr left);
        std::vector<ExprPtr> getArgsArray(TokenType closingType);
        bool checkPriority(int priority, TokenType tokenType);
        bool isUnary(TokenType operation);
        bool checkTokenType(TokenPtr token, TokenType expectedType);
        bool checkSymbolType(SymbolPtr symbol, SymbolType expectedType, TokenPtr token);
        bool checkExprType(ExprPtr expr, SymbolType expectedType);
        SyntaxNodePtr parseStmt();
        SyntaxNodePtr parseStmtIdentifier();
        SyntaxNodePtr parseIf();
        SyntaxNodePtr parseWhile();
        SyntaxNodePtr parseFor();
        SyntaxNodePtr parseBlock();
        SyntaxNodePtr parseEmpty();
        SyntaxNodePtr parseContinue();
        SyntaxNodePtr parseBreak();
        void parseDeclaration(int level, bool isGlobal);
        void parseVarDeclaration(bool isGlobal);
        void parseConstDeclaration();
        void parseTypeDeclaration();
        void parseProcDeclaration(int level);
        void parseFuncDeclaration(int level);
        SymTablePtr parseParams(SymbolPtr proc);
        SymTablePtr parseProcBody(SymbolPtr proc, int level);
        std::vector<TokenPtr> parseIdentifiers();
        bool isDeclaration(TokenType type);
        SymbolPtr parseType();
        SymbolPtr parseSubrange();
        SymbolPtr parsePointer();
        SymbolPtr parseConst(std::string identifier = "");
        SymbolPtr parseRecord();
        SymbolPtr parseArray();
        std::string getSymTableString();
        SymTablePtr getTable(ExprIdentifierPtr identifier);
        void addProcSymbol(std::string name);
        void generateProc(SymbolPtr symbol, int level);
        AsmCode asmCode;
        Scanner scanner;
        std::map<TokenType, int> operationsPriority;
        std::vector<TokenType> unaryOperations;
        SyntaxNodePtr root;
        const int maxOperationPriority = 3;
        std::map<TokenType, std::string> tokensName;
        std::map<SymbolType, std::string> symbolsName;
        SymStack tablesStack;
        std::map<SymbolPtr, SyntaxNodePtr> proceduresBody;
        int procGenCount;
};

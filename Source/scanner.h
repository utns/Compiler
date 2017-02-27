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
        std::ifstream fin;
        std::shared_ptr<Token> token;
        std::string text;
        char peek;
        int line;
        int pos;
        int startLine;
        int startPos;
        std::string buffer;
        std::map<std::string, TokenType> delimiters = {
            {",", TokenType::Comma},
            {";", TokenType::Semicolon},
            {":", TokenType::Colon},
            {"(", TokenType::OpeningParenthesis},
            {")", TokenType::ClosingParenthesis},
            {"[", TokenType::OpeningSquareBracket},
            {"]", TokenType::ClosingSquareBracket},
            {"..", TokenType::DoubleDots},
            {".", TokenType::Dot},
        };
        std::map<std::string, TokenType> operations = {
            {"+", TokenType::Add},
            {"-", TokenType::Sub},
            {"*", TokenType::Mul},
            {"/", TokenType::Div},
            {":=", TokenType::Assignment},
            {"=", TokenType::Equal},
            {"<>", TokenType::NotEqual},
            {"<", TokenType::Less},
            {"<=", TokenType::LessEqual},
            {">=", TokenType::GreatEqual},
            {">", TokenType::Great},
            {"^", TokenType::Hat},
        };
        std::map<std::string, TokenType> reservedWords = {
            {"and",        TokenType::And},
            {"array",      TokenType::Array},
            {"begin",      TokenType::Begin},
            {"break",      TokenType::Break},
            {"case",       TokenType::Case},
            {"const",      TokenType::Const},
            {"continue",   TokenType::Continue},
            {"div",        TokenType::DivRev},
            {"do",         TokenType::Do},
            {"downto",     TokenType::Downto},
            {"else",       TokenType::Else},
            {"end",        TokenType::End},
            {"exit",       TokenType::Exit},
            {"for",        TokenType::For},
            {"function",   TokenType::Function},
            {"goto",       TokenType::Goto},
            {"if",         TokenType::If},
            {"label",      TokenType::Label},
            {"mod",        TokenType::Mod},
            {"nil",        TokenType::Nil},
            {"not",        TokenType::Not},
            {"of",         TokenType::Of},
            {"or",         TokenType::Or},
            {"procedure",  TokenType::Procedure},
            {"program",    TokenType::Program},
            {"record",     TokenType::Record},
            {"repeat",     TokenType::Repeat},
            {"set",        TokenType::Set},
            {"shl",        TokenType::Shl},
            {"shr",        TokenType::Shr},
            {"then",       TokenType::Then},
            {"to",         TokenType::To},
            {"type",       TokenType::Type},
            {"until",      TokenType::Until},
            {"var",        TokenType::Var},
            {"while",      TokenType::While},
            {"xor",        TokenType::Xor},
        };
};

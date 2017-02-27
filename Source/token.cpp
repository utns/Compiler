#include <string>
#include <iostream>
#include "token.h"

Token::Token(int line, int pos, std::string text, TokenType type): line(line), pos(pos), text(text), type(type) {}

int Token::getLine() const {
    return line;
}

int Token::getPos() const {
    return pos;
}

std::string Token::getText() const {
    return text;
}

TokenType Token::getType() const {
    return type;
}

std::string Token::getValue() const {
    return text;
}

int Token::getLenght() const {
    return text.length();
}

IntegerNumber::IntegerNumber(int line, int pos, std::string text, int value): Token(line, pos, text, TokenType::IntegerNumber), value(value) {}

std::string IntegerNumber::getValue() const {
    return std::to_string(value);
}

std::string IntegerNumber::getTypeString() const {
    return "integer number";
}

RealNumber::RealNumber(int line, int pos, std::string text, double value): Token(line, pos, text, TokenType::RealNumber), value(value) {}

std::string RealNumber::getValue() const {
    return std::to_string(value);
}

std::string RealNumber::getTypeString() const {
    return "real number";
}

String::String(int line, int pos, std::string text): Token(line, pos, text, TokenType::String) {
    value = text.substr(1, text.size() - 2);
}

std::string String::getValue() const {
    return value;
}

std::string String::getTypeString() const {
    return "string";
}

EndOfFile::EndOfFile(int line, int pos): Token(line, pos, "end of file", TokenType::EndOfFile) {}

std::string EndOfFile::getTypeString() const {
    return "end of file";
}

Delimiter::Delimiter(int line, int pos, std::string text, TokenType type): Token(line, pos, text, type) {}

std::string Delimiter::getTypeString() const {
    return "delimiter";
}

Operation::Operation(int line, int pos, std::string text, TokenType type): Token(line, pos, text, type) {}

std::string Operation::getTypeString() const {
    return "operation";
}

Word::Word(int line, int pos, std::string text, TokenType type): Token(line, pos, text, type) {}

std::string Word::getTypeString() const {
    return "reserved word";
}

Identifier::Identifier(int line, int pos, std::string text): Token(line, pos, text, TokenType::Identifier) {}

std::string Identifier::getTypeString() const {
    return "identifier";
}

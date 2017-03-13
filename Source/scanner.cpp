#include <iostream>
#include <iomanip>
#include <sstream>
#include "scanner.h"
#include "errors.h"

Scanner::Scanner(const char* fileName): fin(fileName), line(1), pos(0), peek(' ') {
    if (!fin.is_open()) {
        throw IncorrectFile(fileName);
    }
}

std::shared_ptr<Token> Scanner::getNextToken() {
    nextToken();
    return getToken();
}

void Scanner::nextToken()  {
    while (isWhitespace()) {
        readChar();
    }
    if (peek == '{') {
        skipComment();
    }
    text.clear();
    startLine = line;
    startPos = pos;
    if (peek == EOF || (token != nullptr && token->getType() == TokenType::EndOfFile)) {
        setToken(new EndOfFile(startLine, startPos));
        return;
    } else if (isDigit()) {
        getNumber();
        return;
    } else if (peek == '%') {
        getBinary();
        return;
    } else if (peek == '\'') {
        getString();
        return;
    } else if (isDelimiter()) {
        getDelimiter();
        return;
    } else if (isLetter() || peek == '_') {
        getIdentifier();
        return;
    } else if (isOperation()) {
        getOperation();
        return;
    } else {
        throw UnexpectedSymbol(startLine, startPos);
    }
}

std::shared_ptr<Token> Scanner::getToken() {
    return token;
}

bool Scanner::readChar() {
    text.push_back(peek);
    if (!buffer.empty()) {
        peek = buffer.front();
        buffer.erase(0, 1);
    } else {
        peek = fin.get();
    }
    if (peek == '\n') {
        ++line;
        pos = 0;
    } else {
        ++pos;
    }
    peek = tolower(peek);
    return peek != EOF;
}

bool Scanner::isDigit() {
    return peek >= '0' && peek <= '9';
}

bool Scanner::isLetter() {
    return (peek >= 'a' && peek <= 'z') || (peek >= 'A' && peek <= 'Z');
}

void Scanner::getNumber() {
    while (readChar() && isDigit());
    if (peek == '.') {
        if (readChar() && peek == '.') {
            std::string str = text.substr(0, text.size() - 1);
            buffer.push_back('.');
            --this->pos;
            setToken(new IntegerNumber(startLine, startPos, str, std::stoi(str)));
            return;
        } else if (!isDigit()) {
            throw IncorrectFloat(startLine, startPos);
        }
        while (readChar() && isDigit());
        setToken(new RealNumber(startLine, startPos, text, std::stod(text)));
    } else if (peek == 'e') {
        if (readChar() && !(isDigit() || peek == '+' || peek == '-')) {
            throw IncorrectFloat(startLine, startPos);
        } else if ((peek == '+' || peek == '-') && readChar() && !isDigit()) {
            throw IncorrectFloat(startLine, startPos);
        } else {
            while (isDigit() && readChar());
            setToken(new RealNumber(startLine, startPos, text, std::stod(text)));
        }
    } else {
        setToken(new IntegerNumber(startLine, startPos, text, std::stoi(text)));
    }
}

void Scanner::setToken(Token *token) {
    this->token = std::shared_ptr<Token>(token);
    text.clear();
}

void Scanner::getString() {
    while (readChar() && peek != '\n' && peek != '\'');
    if (peek == '\'') {
        readChar();
        setToken(new String(startLine, startPos, text));
    } else {
        throw UnterminatedString(startLine, startPos);
    }
}

void Scanner::skipComment() {
    int line = this->line;
    int pos = this->pos;
    while (readChar() && peek != '}');
    if (peek != '}') {
        throw UnterminatedComment(line, pos);
    }
    while (readChar() && isWhitespace());
}

bool Scanner::isWhitespace() {
    return peek == ' ' || peek == '\t' || peek == '\n';
}

bool Scanner::isDelimiter() {
    std::string str;
    str.push_back(peek);
    return delimiters.find(str) != delimiters.end();
}

void Scanner::getDelimiter() {
    std::string str;
    str.push_back(peek);
    if (peek == '.') {
        if (readChar() && peek == '.') {
            str.push_back('.');
            readChar();
            setToken(new Delimiter(startLine, startPos, str, delimiters[str]));
            return;
        }
    } else if (peek == ':') {
        if (readChar() && peek == '=') {
            str.push_back(peek);
            readChar();
            setToken(new Operation(startLine, startPos, str, operations[str]));
            return;
        }
    } else {
        readChar();
    }
    setToken(new Delimiter(startLine, startPos, str, delimiters[str]));
}

void Scanner::getOperation() {
    readChar();
    std::string str(text);
    str.push_back(peek);
    if (operations.find(str) != operations.end()) {
        readChar();
    }
    setToken(new Operation(startLine, startPos, text, operations[text]));
}

void Scanner::getIdentifier() {
    while (readChar() && (isLetter() || isDigit() || peek == '_'));
    if (reservedWords.find(text) != reservedWords.end()) {
        setToken(new Word(startLine, startPos, text, reservedWords[text]));
    } else {
        setToken(new Identifier(startLine, startPos, text));
    }
}

std::string Scanner::getTokenString() {
    std::stringstream sstream;
    sstream << std::left << std::setw(4) << token->getLine() << " "
            << std::setw(3) << token->getPos() << " "
            << std::setw(15) << token->getTypeString() << " "
            << std::setw(20) << token->getText() << " "
            << token->getValue();
    return sstream.str();
}

std::string Scanner::getTokensString() {
    std::stringstream sstream;
    try {
        while (getNextToken()->getType() != TokenType::EndOfFile) {
            sstream << getTokenString() << std::endl;
        }
    } catch (BaseError& error){
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

void Scanner::getBinary() {
    while (readChar() && (peek == '0' || peek == '1'));
    if (isDigit() && !(peek == '0' || peek == '1')) {
        throw IncorrectBinary(startLine, startPos);
    } else {
        int value = std::stoi(text.substr(1), 0, 2);
        setToken(new IntegerNumber(startLine, startPos, text, value));
    }
}

bool Scanner::isOperation() {
    std::string str;
    str.push_back(peek);
    return operations.find(str) != operations.end();
}

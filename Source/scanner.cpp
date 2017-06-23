#include <iostream>
#include <iomanip>
#include <sstream>
#include "scanner.h"
#include "errors.h"

Scanner::Scanner(const char* fileName): fin(fileName), line(1), pos(0), peek(' '),
        delimiters({
            {",", TokenType::Comma},
            {";", TokenType::Semicolon},
            {":", TokenType::Colon},
            {"(", TokenType::OpeningParenthesis},
            {")", TokenType::ClosingParenthesis},
            {"[", TokenType::OpeningSquareBracket},
            {"]", TokenType::ClosingSquareBracket},
            {"..", TokenType::DoubleDots},
            {".", TokenType::Dot},
        }),
        operations({
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
        }),
        reservedWords({
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
        })
{
    if (!fin.is_open()) {
        throw IncorrectFile(fileName);
    }
}

std::shared_ptr<Token> Scanner::getNextToken() {
    nextToken();
    return getToken();
}

void Scanner::nextToken()  {
//    if (token) {
//        std::cout << token->getText() << std::endl;
//    }
    while (isWhitespace()) {
        readChar();
    }
    if (peek == '{') {
        skipComment();
    } else if (peek == '/') {
        skipSingleLineComment();
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
            setIntegerNumber(str, str);
            return;
        } else if (!isDigit()) {
            throw IncorrectFloat(startLine, startPos);
        }
        while (readChar() && isDigit());
        setFloatNumber(text);
    } else if (peek == 'e') {
        if (readChar() && !(isDigit() || peek == '+' || peek == '-')) {
            throw IncorrectFloat(startLine, startPos);
        } else if ((peek == '+' || peek == '-') && readChar() && !isDigit()) {
            throw IncorrectFloat(startLine, startPos);
        } else {
            while (isDigit() && readChar());
            setFloatNumber(text);
        }
    } else {
        setIntegerNumber(text, text);
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
            << token->getValueStr();
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
        setIntegerNumber(text, text.substr(1), 2);
    }
}

bool Scanner::isOperation() {
    std::string str;
    str.push_back(peek);
    return operations.find(str) != operations.end();
}

void Scanner::skipSingleLineComment() {
    if (readChar() && peek != '/') {
        buffer.push_back('/');
        buffer.push_back(peek);
        pos -= 2;
        readChar();
    } else {
        while (readChar() && peek != '\n');
        readChar();
    }
}

void Scanner::setIntegerNumber(std::string text, std::string value, int base) {
    try {
        setToken(new IntegerNumber(startLine, startPos, text, std::stoi(value, 0, base)));
    } catch (std::out_of_range outOfRange) {
        throw OutOfRangeInteger(startLine, startPos);
    }
}

void Scanner::setFloatNumber(std::string text) {
    try {
        setToken(new FloatNumber(startLine, startPos, text, std::stod(text)));
    } catch (std::out_of_range outOfRange) {
        throw OutOfRangeFloat(startLine, startPos);
    }
}

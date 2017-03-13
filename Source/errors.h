#pragma once

#include <exception>
#include <stdexcept>
#include <string>

class BaseError: public std::exception {
    public:
        BaseError(int line = 0, int pos = 0, std::string msg = "");
        virtual const char* what() const throw();
    protected:
        int line;
        int pos;
        std::string msg;
};

class UnexpectedEOF: public BaseError {
    public:
        UnexpectedEOF(int line, int pos);
};

class UnterminatedString: public BaseError {
    public:
        UnterminatedString(int line, int pos);
};

class UnterminatedComment: public BaseError {
    public:
        UnterminatedComment(int line, int pos);
};

class IncorrectFloat: public BaseError {
    public:
        IncorrectFloat(int line, int pos);
};

class IncorrectInteger: public BaseError {
    public:
        IncorrectInteger(int line, int pos);
};

class IncorrectOperation: public BaseError {
    public:
        IncorrectOperation(int line, int pos);
};

class IncorrectFile: public BaseError {
    public:
        IncorrectFile(std::string fileName);
};

class IncorrectBinary: public BaseError {
    public:
        IncorrectBinary(int line, int pos);
};

class UnexpectedSymbol: public BaseError {
    public:
        UnexpectedSymbol(int line, int pos);
};

class SyntaxError: public BaseError {
    public:
        SyntaxError(int line, int pos, std::string msg);
};

class IllegalExpression: public SyntaxError {
    public:
        IllegalExpression(int line, int pos);
};

class ExpectedError: public SyntaxError {
    public:
        ExpectedError(int line, int pos, std::string expected, std::string found);
};
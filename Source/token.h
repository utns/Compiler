#pragma once

#include <string>
#include <memory>

enum class TokenType {
    And,
    Array,
    Begin,
    Break,
    Case,
    Const,
    Continue,
    DivRev,
    Do,
    Downto,
    Else,
    End,
    Exit,
    For,
    Function,
    Goto,
    If,
    Label,
    Mod,
    Nil,
    Not,
    Of,
    Or,
    Procedure,
    Program,
    Record,
    Repeat,
    Set,
    Shl,
    Shr,
    Then,
    To,
    Type,
    Until,
    Var,
    While,
    Xor,

    Add,
    Sub,
    Mul,
    Div,
    Assignment,
    Equal,
    NotEqual,
    Less,
    LessEqual,
    GreatEqual,
    Great,
    Hat,

    Comma,
    Semicolon,
    Colon,
    OpeningParenthesis,
    ClosingParenthesis,
    OpeningSquareBracket,
    ClosingSquareBracket,
    DoubleDots,
    Dot,

    Identifier,
    Word,
    IntegerNumber,
    FloatNumber,
    String,
    Delimiter,
    Operation,
    EndOfFile,
};

class Token {
    public:
        Token(int line, int pos, std::string text, TokenType type);
        int getLine() const;
        int getPos() const;
        std::string getText() const;
        TokenType getType() const;
        virtual std::string getValueStr() const;
        virtual std::string getTypeString() const = 0;
    private:
        int line;
        int pos;
        std::string text;
        TokenType type;
};

typedef std::shared_ptr<Token> TokenPtr;

class Identifier: public Token {
    public:
        Identifier(int line, int pos, std::string text);
        std::string getTypeString() const;
};

class Word: public Token {
    public:
        Word(int line, int pos, std::string text, TokenType type);
        std::string getTypeString() const;
};

class IntegerNumber: public Token {
    public:
        IntegerNumber(int line, int pos, std::string text, int value);
        std::string getValueStr() const;
        std::string getTypeString() const;
        int getValue();
    private:
        int value;
};

class FloatNumber: public Token {
    public:
        FloatNumber(int line, int pos, std::string text, double value);
        std::string getValueStr() const;
        std::string getTypeString() const;
        double getValue();
    private:
        double value;
};

class String: public Token {
    public:
        String(int line, int pos, std::string text);
        std::string getValueStr() const;
        std::string getTypeString() const;
    private:
        std::string value;
};

class Delimiter: public Token {
    public:
        Delimiter(int line, int pos, std::string text, TokenType type);
        std::string getTypeString() const;
};

class Operation: public Token {
    public:
        Operation(int line, int pos, std::string text, TokenType type);
        std::string getTypeString() const;
};

class EndOfFile: public Token {
    public:
        EndOfFile(int line, int pos);
        std::string getTypeString() const;
};

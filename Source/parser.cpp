#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "parser.h"
#include "errors.h"

Parser::Parser(const char* fileName): scanner(fileName) {
    operationsPriority[TokenType::Equal] = 0;
    operationsPriority[TokenType::NotEqual] = 0;
    operationsPriority[TokenType::Less] = 0;
    operationsPriority[TokenType::Great] = 0;
    operationsPriority[TokenType::LessEqual] = 0;
    operationsPriority[TokenType::GreatEqual] = 0;

    operationsPriority[TokenType::Add] = 1;
    operationsPriority[TokenType::Sub] = 1;
    operationsPriority[TokenType::Or] = 1;
    operationsPriority[TokenType::Xor] = 1;

    operationsPriority[TokenType::Mul] = 2;
    operationsPriority[TokenType::Div] = 2;
    operationsPriority[TokenType::DivRev] = 2;
    operationsPriority[TokenType::Mod] = 2;
    operationsPriority[TokenType::And] = 2;
    operationsPriority[TokenType::Shl] = 2;
    operationsPriority[TokenType::Shr] = 2;

    unaryOperations = {TokenType::Not, TokenType::Add, TokenType::Sub};
}

void Parser::parse() {
    scanner.nextToken();
    root = parseExpr(0);
}

ExprPtr Parser::parseExpr(int priority) {
    if (priority == maxOperationPriority) {
        return parseFactor();
    }
    ExprPtr left = parseExpr(priority + 1);
    TokenPtr token = scanner.getToken();
    while (checkPriority(priority, token->getType())) {
        scanner.nextToken();
        ExprPtr right = parseExpr(priority + 1);
        left = ExprPtr(new ExprBinaryOp(token, left, right));
        token = scanner.getToken();
    }
    return left;
}

ExprPtr Parser::parseFactor() {
    ExprPtr expr;
    TokenPtr token = scanner.getToken();
    scanner.nextToken();
    if (scanner.getToken()->getType() == TokenType::OpeningSquareBracket &&
            token->getType() != TokenType::Identifier) {
        throw IllegalExpression(token->getLine(), token->getPos());
    }
    if (isUnary(token->getType())) {
        return ExprPtr(new ExprUnaryOp(token, parseFactor()));
    }
    switch (token->getType()) {
        case TokenType::Identifier:
            return parseIdentifier(token);
        case TokenType::IntegerNumber:
            return ExprPtr(new ExprInteger(token));
        case TokenType::RealNumber:
            return ExprPtr(new ExprReal(token));
        case TokenType::OpeningParenthesis:
            expr = parseExpr(0);
            checkTokenType(scanner.getToken(), TokenType::ClosingParenthesis, ")");
            scanner.nextToken();
            return expr;
        default:
            throw IllegalExpression(token->getLine(), token->getPos());
    }
}

bool Parser::checkPriority(int priority, TokenType tokenType) {
    return operationsPriority.find(tokenType) != operationsPriority.end() && operationsPriority[tokenType] == priority;
}

bool Parser::isUnary(TokenType operation) {
    for (auto type: unaryOperations) {
        if (type == operation) {
            return true;
        }
    }
    return false;
}

bool Parser::checkTokenType(TokenPtr token, TokenType expectedType, std::string expected) {
    if (token->getType() != expectedType) {
        throw ExpectedError(token->getLine(), token->getPos(), expected, scanner.getToken()->getValue());
    }
    return true;
}

std::vector<ExprPtr> Parser::getArrayIndexes() {
    std::vector<ExprPtr> indexes;
    indexes.push_back(parseExpr(0));
    while (scanner.getToken()->getType() != TokenType::ClosingSquareBracket) {
        checkTokenType(scanner.getToken(), TokenType::Comma, ",");
        TokenPtr token = scanner.getToken();
        if (scanner.getNextToken()->getType() == TokenType ::ClosingSquareBracket) {
            throw ExpectedError(token->getLine(), token->getPos(), "]", token->getValue());
        };
        indexes.push_back(parseExpr(0));
    }
    scanner.nextToken();
    std::reverse(indexes.begin(), indexes.end());
    return indexes;
}

ExprPtr Parser::parseIdentifier(TokenPtr token) {
    ExprPtr left(new ExprIdentifier(token));
    left = parseArrayAccess(left);
    TokenPtr dotToken = scanner.getToken();
    while (dotToken->getType() == TokenType::Dot) {
        checkTokenType(scanner.getNextToken(), TokenType::Identifier, "identifier");
        token = scanner.getToken();
        scanner.nextToken();
        left = ExprPtr(new ExprRecordAccess(dotToken, left, ExprPtr(new ExprIdentifier(token))));
        left = parseArrayAccess(left);
        dotToken = scanner.getToken();
    }
    return left;
}

std::string Parser::getTreeString() {
    std::stringstream sstream;
    try {
        parse();
        sstream << root->getString(0);
    } catch (BaseError& error) {
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

ExprPtr Parser::parseArrayAccess(ExprPtr left) {
    TokenPtr token = scanner.getToken();
    if (token->getType() == TokenType::OpeningSquareBracket) {
        scanner.nextToken();
        std::vector<ExprPtr> indexes = getArrayIndexes();
        left = ExprPtr(new ExprArrayAccess(token, left, indexes));
    }
    return left;
}

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "syntaxnodes.h"

Expr::Expr(TokenPtr token, ExprType exprType): token(token), exprType(exprType) {}

TokenPtr Expr::getToken() {
    return token;
}

std::string Expr::getString(int depth) {
    std::stringstream sstream;
    sstream << std::setw(spacesCount * depth) << std::string(depth == 0?0:1 * spacesCount - token->getValue().size(), '_') + token->getValue() << std::endl;
    return sstream.str();
}

ExprIdentifier::ExprIdentifier(TokenPtr token) : Expr(token, ExprType::ExprIdentifier) {}

ExprConst::ExprConst(TokenPtr token, ExprType exprType) : Expr(token, exprType) {}

ExprInteger::ExprInteger(TokenPtr token): ExprConst(token, ExprType::ExprInteger) {}

ExprReal::ExprReal(TokenPtr token): ExprConst(token, ExprType::ExprFloat) {}

ExprString::ExprString(TokenPtr token): ExprConst(token, ExprType::ExprString) {}

ExprOp::ExprOp(TokenPtr token, ExprType exprType) : Expr(token, exprType) {}

std::string ExprBinaryOp::getString(int depth) {
    std::stringstream sstream;
    sstream << right->getString(depth + 1);
    sstream << Expr::getString(depth);
    sstream << left->getString(depth + 1);
    return sstream.str();
}

ExprBinaryOp::ExprBinaryOp(TokenPtr token, ExprPtr left, ExprPtr right, ExprType exprType):
    ExprOp(token, exprType), left(left), right(right) {}

ExprUnaryOp::ExprUnaryOp(TokenPtr token, ExprPtr expr): ExprOp(token, ExprType::ExprUnaryOp), expr(expr) {}
std::string ExprUnaryOp::getString(int depth) {
    std::stringstream sstream;
    sstream << expr->getString(depth + 1);
    sstream << Expr::getString(depth);
    return sstream.str();
}

ExprArrayAccess::ExprArrayAccess(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes): Expr(token, ExprType::ExprArrayAccess),
                                                                                             nodes(nodes), ident(ident) {}

std::string ExprArrayAccess::getString(int depth) {
    std::stringstream sstream;
    for (auto expr: nodes) {
        sstream << expr->getString(depth + 1);
    }
    sstream << Expr::getString(depth);
    sstream << ident->getString(depth + 1);
    return sstream.str();
}

ExprRecordAccess::ExprRecordAccess(TokenPtr token, ExprPtr left,
                                   ExprPtr right) : ExprBinaryOp(token, left, right, ExprType::ExprRecordAccess) {
}

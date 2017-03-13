#pragma once

#include <memory>
#include <vector>
#include "token.h"

enum class ExprType {
    ExprIdentifier, ExprInteger, ExprFloat, ExprString, ExprBinaryOp, ExprUnaryOp, ExprArrayAccess, ExprRecordAccess,
};

class Expr {
    public:
        Expr(TokenPtr token, ExprType exprType);
        virtual std::string getString(int depth);
        TokenPtr getToken();
    private:
        TokenPtr token;
        ExprType exprType;
        const static int spacesCount = 5;
};

typedef std::shared_ptr<Expr> ExprPtr;

class ExprIdentifier: public Expr {
    public:
        ExprIdentifier(TokenPtr token);
};

class ExprConst: public Expr {
    public:
        ExprConst(TokenPtr token, ExprType exprType);
};

class ExprInteger: public ExprConst {
    public:
        ExprInteger(TokenPtr token);
};

class ExprReal: public ExprConst {
    public:
        ExprReal(TokenPtr token);
};

class ExprString: public ExprConst {
    public:
        ExprString(TokenPtr token);
};

class ExprOp: public Expr {
    public:
        ExprOp(TokenPtr token, ExprType exprType);
};

class ExprBinaryOp: public ExprOp {
    public:
        ExprBinaryOp(TokenPtr token, ExprPtr left, ExprPtr right, ExprType exprType = ExprType::ExprBinaryOp);
        std::string getString(int depth) override;
    private:
        ExprPtr left;
        ExprPtr right;
};

class ExprUnaryOp: public ExprOp {
    public:
        ExprUnaryOp(TokenPtr token, ExprPtr expr);
        std::string getString(int depth) override;
    private:
        ExprPtr expr;

};

class ExprArrayAccess: public Expr {
    public:
        ExprArrayAccess(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes);
        std::string getString(int depth) override;
    private:
        std::vector<ExprPtr> nodes;
        ExprPtr ident;
};

class ExprRecordAccess: public ExprBinaryOp {
    public:
        ExprRecordAccess(TokenPtr token, ExprPtr left, ExprPtr right);
};
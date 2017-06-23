#pragma once

#include <memory>
#include <vector>
#include "token.h"
#include "symbols.h"
#include "asmgen.h"

enum class NodeType {
    ExprIdentifier,
    ExprInteger,
    ExprFloat,
    ExprString,
    ExprBinaryOp,
    ExprUnaryOp,
    ExprArrayAccess,
    ExprRecordAccess,
    ExprCall,
    ExprAssignOp,
    ExprRealTypecast,
    StmtBlock,
    StmtIf,
    StmtWhile,
    StmtFor,
    StmtEmpty,
    StmtContinue,
    StmtBreak,
};

class SyntaxNode {
    public:
        SyntaxNode(NodeType nodeType);
        virtual std::string getString(int depth) = 0;
        NodeType getNodeType();
        virtual SymbolType getType();
        virtual void generate(AsmCode& asmCode);
        virtual int getSize();
    protected:
        std::string getTreeString(int depth, std::string str);
    private:
        NodeType type;
        const static int spacesCount = 5;
};

typedef std::shared_ptr<SyntaxNode> SyntaxNodePtr;

class StmtBlock: public SyntaxNode {
    public:
        StmtBlock();
        void addStatment(SyntaxNodePtr stmt);
        std::string getString(int depth) override ;
        void generate(AsmCode& asmCode) override ;
    private:
        std::vector<SyntaxNodePtr> statments;
};

typedef std::shared_ptr<StmtBlock> StmtBlockPtr;

class Expr: public SyntaxNode {
    public:
        Expr(TokenPtr token, NodeType nodeType);
        std::string getString(int depth);
        TokenPtr getToken();
        virtual void generateLValue(AsmCode &asmCode);
        virtual bool isLocal();
    protected:
        std::map<SymbolType, std::string> symbolToString;
    private:
        TokenPtr token;
};

typedef std::shared_ptr<Expr> ExprPtr;

class StmtNode: public SyntaxNode {
    public:
        StmtNode(NodeType nodeType);
};

class StmtIf: public  StmtNode {
    public:
        StmtIf(ExprPtr expr, SyntaxNodePtr thenStmt, SyntaxNodePtr elseStmt);
        std::string getString(int depth) override;
        void generate(AsmCode& asmCode) override;
    private:
        ExprPtr expr;
        SyntaxNodePtr thenStmt;
        SyntaxNodePtr elseStmt;
};

class StmtWhile: public StmtNode {
    public:
        StmtWhile(ExprPtr expr, SyntaxNodePtr stmt);
        std::string getString(int depth) override;
        void generate(AsmCode& asmCode) override;
    private:
        ExprPtr expr;
        SyntaxNodePtr stmt;
};

class StmtFor: public StmtNode {
    public:
        StmtFor(SymbolPtr var, ExprPtr initExpr, ExprPtr finalExpr, SyntaxNodePtr stmt, bool isTo);
        std::string getString(int depth) override;
        void generate(AsmCode& asmCode) override;
    private:
        void generateCond(AsmCode& asmCode);
        SymbolPtr var;
        ExprPtr initExpr, finalExpr;
        SyntaxNodePtr stmt;
        bool isTo;
};

class StmtEmpty: public StmtNode {
    public:
        StmtEmpty();
        std::string getString(int depth) override;
};

class StmtContinue: public StmtNode {
    public:
        StmtContinue();
        std::string getString(int depth) override;
        void generate(AsmCode& asmCode) override;
};

class StmtBreak: public StmtNode {
    public:
        StmtBreak();
        std::string getString(int depth) override;
        void generate(AsmCode& asmCode) override;
};

class ExprIdentifier: public Expr {
    public:
        ExprIdentifier(TokenPtr token, SymbolPtr symbol);
        SymbolType getType() override;
        int getSize() override;
        SymbolPtr getSymbol();
        void generateLValue(AsmCode &asmCode) override;
        void generate(AsmCode &asmCode) override; 
        bool isLocal() override;
    private:
        SymbolPtr symbol;
};

typedef std::shared_ptr<ExprIdentifier> ExprIdentifierPtr;

class ExprConst: public Expr {
    public:
        ExprConst(TokenPtr token, NodeType nodeType);
};

class ExprInteger: public ExprConst {
    public:
        ExprInteger(TokenPtr token);
        SymbolType getType() override;
        void generate(AsmCode& asmCode) override;
};

class ExprReal: public ExprConst {
    public:
        ExprReal(TokenPtr token);
        SymbolType getType() override;
        void generate(AsmCode& asmCode) override;
};

class ExprString: public ExprConst {
    public:
        ExprString(TokenPtr token);
        SymbolType getType() override;
};

class ExprOp: public Expr {
    public:
        ExprOp(TokenPtr token, NodeType nodeType);
};

class ExprBinaryOp: public ExprOp {
    public:
        ExprBinaryOp(TokenPtr token, ExprPtr left, ExprPtr right, NodeType exprType = NodeType::ExprBinaryOp);
        std::string getString(int depth) override;
        SymbolType getType() override;
        ExprPtr getLeft();
        ExprPtr getRight();
        void generate(AsmCode& asmCode) override;
    protected:
        void generateInt(AsmCode& asmCode);
        void generateIntRelation(AsmCode& asmCode);
        void generateFloat(AsmCode& asmCode);
        void generateFloatRelation(AsmCode& asmCode);
        void generateAnd(AsmCode& asmCode);
        void generateOr(AsmCode& asmCode);
        bool isRelationOp();
        ExprPtr left;
        ExprPtr right;
};

class ExprUnaryOp: public ExprOp {
    public:
        ExprUnaryOp(TokenPtr token, ExprPtr expr);
        std::string getString(int depth);
        SymbolType getType();
        void generate(AsmCode& asmCode) override;
    private:
        ExprPtr expr;
};

class ExprRealTypecast: public ExprOp {
    public:
        ExprRealTypecast(ExprPtr expr);
        std::string getString(int depth) override;
        SymbolType getType() override;
        void generate(AsmCode& asmCode) override;
    private:
        ExprPtr expr;
};

class ExprArrayAccess: public Expr {
    public:
        ExprArrayAccess(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes);
        std::string getString(int depth) override;
        SymbolType getType() override;
        ExprIdentifierPtr getIdentifier();
        SymbolPtr getRefSymbol();
        SymTypeArrayPtr getTypeArraySymbol();
        void generate(AsmCode &asmCode) override;
        void generateLValue(AsmCode &asmCode) override;
        bool isLocal() override;
    private:
        void generateIndex(AsmCode &asmCode);
        std::vector<ExprPtr> nodes;
        ExprPtr ident;
};

class ExprCall: public Expr {
    public:
        ExprCall(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes, SymbolPtr symbol = SymbolPtr());
        std::string getString(int depth) override;
        void generate(AsmCode &asmCode) override;
        SymbolType getType() override;
    protected:
        std::vector<ExprPtr> nodes;
        ExprPtr ident;
        SymProcBasePtr symbol;
};

class ExprWrite: public ExprCall {
public:
    ExprWrite(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes);
    void generate(AsmCode &asmCode) override;
};

class ExprWriteln: public ExprWrite {
public:
    ExprWriteln(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes);
    void generate(AsmCode &asmCode) override;
};

class ExprRecordAccess: public ExprBinaryOp {
    public:
        ExprRecordAccess(TokenPtr token, ExprPtr left, ExprPtr right);
        SymbolType getType() override;
        void generate(AsmCode &asmCode) override;
        void generateLValue(AsmCode &asmCode) override;
        bool isLocal() override;
};

typedef std::shared_ptr<ExprRecordAccess> ExprRecordAccessPtr;

class ExprAssignOp: public ExprBinaryOp {
    public:
        ExprAssignOp(TokenPtr token, ExprPtr left, ExprPtr right);
        void generate(AsmCode& asmCode) override;
};
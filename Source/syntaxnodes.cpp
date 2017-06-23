#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "syntaxnodes.h"
#include "symbols.h"

Expr::Expr(TokenPtr token, NodeType nodeType): SyntaxNode(nodeType), token(token), 
    symbolToString({
        {SymbolType::VarParam, "VarParam"},
        {SymbolType::Param, "Param"},
        {SymbolType::VarConst, "VarConst"},
        {SymbolType::VarLocal, "VarLocal"},
        {SymbolType::VarGlobal, "VarGlobal"},
        {SymbolType::TypeFloat, "TypeFloat"},
        {SymbolType::TypeInteger, "TypeInteger"},
        {SymbolType::TypeChar, "TypeChar"},
        {SymbolType::TypeArray, "TypeArray"},
        {SymbolType::TypeOpenArray, "TypeOpenArray"},
        {SymbolType::TypePointer, "TypePointer"},
        {SymbolType::TypeRecord, "TypeRecord"},
        {SymbolType::TypeAlias, "TypeAlias"},
        {SymbolType::TypeSubrange, "TypeSubrange"},
        {SymbolType::TypeString, "TypeString"},
        {SymbolType::Proc, "Proc"},
        {SymbolType::Func, "Func"},
        {SymbolType::ConstInteger, "ConstInteger"},
        {SymbolType::ConstFloat, "ConstFloat"},
        {SymbolType::None, "None"},
    }) {}

TokenPtr Expr::getToken() {
    return token;
}

std::string Expr::getString(int depth) {
//    std::cout << token->getValueStr() << std::endl;
//    std::cout << getTreeString(depth, token->getValueStr() + " " + symbolToString[getType()]);
    return getTreeString(depth, token->getValueStr() + " " + symbolToString[getType()]);
//    return getTreeString(depth, token->getValueStr());
}

void Expr::generateLValue(AsmCode &asmCode) {

}

bool Expr::isLocal() {
    false;
}

ExprIdentifier::ExprIdentifier(TokenPtr token, SymbolPtr symbol): Expr(token, NodeType::ExprIdentifier), symbol(symbol) {}

SymbolType ExprIdentifier::getType() {
    if (symbol->getType() == SymbolType::Proc
        || symbol->getType() == SymbolType::TypeRecord) {
        return symbol->getType();
    } else if (symbol->getType() == SymbolType::Func) {
        return std::dynamic_pointer_cast<SymProcBase>(symbol)->getArgs()->getSymbol("result")->getVarType();
    } else {
        return symbol->getVarType();
    }
}

SymbolPtr ExprIdentifier::getSymbol() {
    return symbol;
}

void ExprIdentifier::generateLValue(AsmCode &asmCode) {
    symbol->generateLValue(asmCode);
}

void ExprIdentifier::generate(AsmCode &asmCode) {
    symbol->generateValue(asmCode);
//    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(asmCode.getVarName(symbol->getName())));
//    asmCode.addCmd(PUSH, RAX);
}

bool ExprIdentifier::isLocal() {
    return !(symbol->getType() == SymbolType::VarGlobal || symbol->getType() == SymbolType::VarParam);
}

int ExprIdentifier::getSize() {
    if (symbol->getType() == SymbolType::Proc
        || symbol->getType() == SymbolType::TypeRecord) {
        return symbol->getSize();
    } else if (symbol->getType() == SymbolType::Func) {
        return std::dynamic_pointer_cast<SymVar>(
                std::dynamic_pointer_cast<SymProcBase>(symbol)->getArgs()->getSymbol("result"))->getSize();
    } else {
        return std::dynamic_pointer_cast<SymVar>(symbol)->getSize();
    }
}

ExprConst::ExprConst(TokenPtr token, NodeType nodeType) : Expr(token, nodeType) {}

ExprInteger::ExprInteger(TokenPtr token): ExprConst(token, NodeType::ExprInteger) {}

SymbolType ExprInteger::getType() {
    return SymbolType::TypeInteger;
}

void ExprInteger::generate(AsmCode &asmCode) {
    asmCode.addCmd(MOV, RAX, std::stoi(getToken()->getValueStr()));
    asmCode.addCmd(PUSH, RAX);
}

ExprReal::ExprReal(TokenPtr token): ExprConst(token, NodeType::ExprFloat) {}

SymbolType ExprReal::getType() {
    return SymbolType::TypeFloat;
}

void ExprReal::generate(AsmCode &asmCode) {
    std::string name = asmCode.genVarName();
    asmCode.addData(name, std::stod(getToken()->getValueStr()));
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(name));
    asmCode.addCmd(PUSH, RAX);
}

ExprString::ExprString(TokenPtr token): ExprConst(token, NodeType::ExprString) {}

SymbolType ExprString::getType() {
    return SymbolType::TypeString;
}

ExprOp::ExprOp(TokenPtr token, NodeType nodeType): Expr(token, nodeType) {}

std::string ExprBinaryOp::getString(int depth) {
    std::stringstream sstream;
    sstream << right->getString(depth + 1);
    sstream << Expr::getString(depth);
    sstream << left->getString(depth + 1);
    return sstream.str();
}

ExprBinaryOp::ExprBinaryOp(TokenPtr token, ExprPtr left, ExprPtr right, NodeType exprType):
    ExprOp(token, exprType), left(left), right(right) {}

SymbolType ExprBinaryOp::getType() {
//    std::cout << " left " << left->getString(0) << std::endl;
    if (isRelationOp()) {
        return SymbolType::TypeInteger;
    }
    SymbolType leftType = left->getType();
    SymbolType rightType = right->getType();
    if (leftType == rightType) {
        return leftType;
    } else if (leftType == SymbolType::TypeFloat && rightType == SymbolType::TypeInteger) {
        right = std::make_shared<ExprRealTypecast>(right);
        return leftType; 
    } else if (leftType == SymbolType::TypeInteger && rightType == SymbolType::TypeFloat) {
        left = std::make_shared<ExprRealTypecast>(left);
        return rightType;
    }
    return Expr::getType();
}

ExprPtr ExprBinaryOp::getLeft() {
    return left;
}

ExprPtr ExprBinaryOp::getRight() {
    return right;
}

void ExprBinaryOp::generate(AsmCode &asmCode) {
    left->generate(asmCode);
    right->generate(asmCode);
    if (left->getType() == SymbolType::TypeInteger) {
        generateInt(asmCode);
    } else if (left->getType() == SymbolType::TypeFloat) {
        generateFloat(asmCode);
    }
}

void ExprBinaryOp::generateInt(AsmCode &asmCode) {
    asmCode.addCmd(POP, RBX);
    asmCode.addCmd(POP, RAX);
    switch (getToken()->getType()) {
        case TokenType::Add:
            asmCode.addCmd(ADD, RAX, RBX);
            break;
        case TokenType::Sub:
            asmCode.addCmd(SUB, RAX, RBX);
            break;
        case TokenType::Mul:
            asmCode.addCmd(IMUL, RBX);
            break;
        case TokenType::DivRev:
            asmCode.addCmd(XOR, RDX, RDX);
            asmCode.addCmd(IDIV, RBX);
            break;
        case TokenType::Mod:
            asmCode.addCmd(XOR, RDX, RDX);
            asmCode.addCmd(IDIV, RBX);
            asmCode.addCmd(MOV, RAX, RDX);
            break;
        case TokenType::And:
            generateAnd(asmCode);
            break;
        case TokenType::Or:
            generateOr(asmCode);
            break;
        default:
            generateIntRelation(asmCode);
            break;
    }
    asmCode.addCmd(PUSH, RAX);
}

void ExprBinaryOp::generateIntRelation(AsmCode &asmCode) {
    asmCode.addCmd(CMP, RAX, RBX);
    std::string label1 = asmCode.genLabelName();
    std::string label2 = asmCode.genLabelName();
    switch (getToken()->getType()) {
        case TokenType::Equal:
            asmCode.addCmd(JE, label1);
            break;
        case TokenType::NotEqual:
            asmCode.addCmd(JNE, label1);
            break;
        case TokenType::Less:
            asmCode.addCmd(JL, label1);
            break;
        case TokenType::LessEqual:
            asmCode.addCmd(JLE, label1);
            break;
        case TokenType::GreatEqual:
            asmCode.addCmd(JGE, label1);
            break;
        case TokenType::Great:
            asmCode.addCmd(JG, label1);
            break;
    }
    asmCode.addCmd(MOV, RAX, 0);
    asmCode.addCmd(JMP, label2);
    asmCode.addLabel(label1);
    asmCode.addCmd(MOV, RAX, 1);
    asmCode.addLabel(label2);
}

void ExprBinaryOp::generateFloat(AsmCode &asmCode) {
    asmCode.addCmd(POP, RBX);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOVQ, XMM0, RAX);
    asmCode.addCmd(MOVQ, XMM1, RBX);
    bool isRelation = false;
    switch (getToken()->getType()) {
        case TokenType::Add:
            asmCode.addCmd(ADDSD, XMM0, XMM1);
            break;
        case TokenType::Sub:
            asmCode.addCmd(SUBSD, XMM0, XMM1);
            break;
        case TokenType::Mul:
            asmCode.addCmd(MULSD, XMM0, XMM1);
            break;
        case TokenType::Div:
            asmCode.addCmd(DIVSD, XMM0, XMM1);
            break;
        default:
            isRelation = true;
            generateFloatRelation(asmCode);
            break;
    }
    if (!isRelation) {
        asmCode.addCmd(MOVQ, RAX, XMM0);
    }
    asmCode.addCmd(PUSH, RAX);
}

void ExprBinaryOp::generateFloatRelation(AsmCode &asmCode) {
    asmCode.addCmd(COMISD, XMM0, XMM1);
    std::string label1 = asmCode.genLabelName();
    std::string label2 = asmCode.genLabelName();
    switch (getToken()->getType()) {
        case TokenType::Equal:
            asmCode.addCmd(JE, label1);
            break;
        case TokenType::NotEqual:
            asmCode.addCmd(JNE, label1);
            break;
        case TokenType::Less:
            asmCode.addCmd(JB, label1);
            break;
        case TokenType::LessEqual:
            asmCode.addCmd(JBE, label1);
            break;
        case TokenType::GreatEqual:
            asmCode.addCmd(JAE, label1);
            break;
        case TokenType::Great:
            asmCode.addCmd(JA, label1);
            break;
    }
    asmCode.addCmd(MOV, RAX, 0);
    asmCode.addCmd(JMP, label2);
    asmCode.addLabel(label1);
    asmCode.addCmd(MOV, RAX, 1);
    asmCode.addLabel(label2);
}

bool ExprBinaryOp::isRelationOp() {
    TokenType type = getToken()->getType();
    return type == TokenType::Equal || type == TokenType::NotEqual 
           || type == TokenType::Less || type == TokenType::LessEqual
           || type == TokenType::GreatEqual || type == TokenType::Great;
}

void ExprBinaryOp::generateAnd(AsmCode& asmCode) {
    std::string label1 = asmCode.genLabelName();
    std::string label2 = asmCode.genLabelName();
    asmCode.addCmd(TEST, RAX, RAX);
    asmCode.addCmd(JZ, label1);
    asmCode.addCmd(TEST, RBX, RBX);
    asmCode.addCmd(JZ, label1);
    asmCode.addCmd(MOV, RAX, 1);
    asmCode.addCmd(JMP, label2);
    asmCode.addLabel(label1);
    asmCode.addCmd(MOV, RAX, 0);
    asmCode.addLabel(label2);
}

void ExprBinaryOp::generateOr(AsmCode& asmCode) {
    std::string label1 = asmCode.genLabelName();
    std::string label2 = asmCode.genLabelName();
    asmCode.addCmd(TEST, RAX, RAX);
    asmCode.addCmd(JNZ, label1);
    asmCode.addCmd(TEST, RBX, RBX);
    asmCode.addCmd(JNZ, label1);
    asmCode.addCmd(MOV, RAX, 0);
    asmCode.addCmd(JMP, label2);
    asmCode.addLabel(label1);
    asmCode.addCmd(MOV, RAX, 1);
    asmCode.addLabel(label2);
}

ExprUnaryOp::ExprUnaryOp(TokenPtr token, ExprPtr expr): ExprOp(token, NodeType::ExprUnaryOp), expr(expr) {}

std::string ExprUnaryOp::getString(int depth) {
    std::stringstream sstream;
    sstream << expr->getString(depth + 1);
    sstream << Expr::getString(depth);
    return sstream.str();
}

SymbolType ExprUnaryOp::getType() {
    return expr->getType();
}

void ExprUnaryOp::generate(AsmCode &asmCode) {
    expr->generate(asmCode);
    if (expr->getType() == SymbolType::TypeInteger) {
        asmCode.addCmd(POP, RAX);
        switch (getToken()->getType()) {
            case TokenType::Sub:
                asmCode.addCmd(NEG, RAX);
                break;
            case TokenType::Not:
                asmCode.addCmd(XOR, RAX, 1);
        }
        asmCode.addCmd(PUSH, RAX);
    } else if (expr->getType() == SymbolType::TypeFloat && getToken()->getType() == TokenType::Sub) {
        unsigned long long int signBit = 1;
        signBit <<= 63;
        asmCode.addCmd(POP, RAX);
        asmCode.addCmd(MOV, RBX, std::to_string(signBit));
        asmCode.addCmd(XOR, RAX, RBX);
        asmCode.addCmd(PUSH, RAX);
    }
}


ExprRealTypecast::ExprRealTypecast(ExprPtr expr): ExprOp(TokenPtr(), NodeType::ExprRealTypecast), expr(expr) {}

std::string ExprRealTypecast::getString(int depth) {
    std::stringstream sstream;
    sstream << expr->getString(depth + 1);
    sstream << getTreeString(depth, "RCast");
    return sstream.str();
}

SymbolType ExprRealTypecast::getType() {
    return SymbolType::TypeFloat;
}

void ExprRealTypecast::generate(AsmCode &asmCode) {
    expr->generate(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(CVTSI2SD, XMM0, RAX);
    asmCode.addCmd(MOVQ, RAX, XMM0);
    asmCode.addCmd(PUSH, RAX);
}


ExprArrayAccess::ExprArrayAccess(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes): Expr(token, NodeType::ExprArrayAccess),
                                                                                             nodes(nodes), ident(ident) {}

std::string ExprArrayAccess::getString(int depth) {
    std::stringstream sstream;
    for (int i = nodes.size() - 1; i >= 0; --i) {
        sstream << nodes[i]->getString(depth + 1);
    }
    sstream << Expr::getString(depth);
    sstream << ident->getString(depth + 1);
    return sstream.str();
}

SymbolType ExprArrayAccess::getType() {
    return getTypeArraySymbol()->getElemType();
}

ExprIdentifierPtr ExprArrayAccess::getIdentifier() {
    if (ident->getNodeType() == NodeType::ExprIdentifier) {
        return std::dynamic_pointer_cast<ExprIdentifier>(ident);
    } else {
        return std::dynamic_pointer_cast<ExprIdentifier>(std::dynamic_pointer_cast<ExprRecordAccess>(ident)->getRight());
    }
}

SymbolPtr ExprArrayAccess::getRefSymbol() {
    SymbolPtr elemSymbol = getTypeArraySymbol()->getElemSybmol();
    return std::dynamic_pointer_cast<SymTypeAlias>(elemSymbol)->getRefSymbol();
}

void ExprArrayAccess::generateLValue(AsmCode &asmCode) {
    generateIndex(asmCode);
}

void ExprArrayAccess::generateIndex(AsmCode &asmCode) {
    ident->generateLValue(asmCode);
    SymbolPtr type = std::dynamic_pointer_cast<SymVar>(getIdentifier()->getSymbol())->getTypeSymbol();
    int lowRange = 0;
    AsmOpType asmOp;
    if (!ident->isLocal()) {
        asmOp = ADD;
    } else {
        asmOp = SUB;
    }
    for (auto node: nodes) {
        if (type->getType() == SymbolType::TypeArray) {
            lowRange = std::dynamic_pointer_cast<SymTypeArray>(type)->getLowRange();
            type = std::dynamic_pointer_cast<SymTypeArray>(type)->getElemSybmol();
        }
        node->generate(asmCode);
        asmCode.addCmd(POP, RAX);
        asmCode.addCmd(MOV, RBX, lowRange);
        asmCode.addCmd(SUB, RAX, RBX);
        asmCode.addCmd(MOV, RBX, type->getSize());
        asmCode.addCmd(IMUL, RBX);
        asmCode.addCmd(POP, RBX);
        asmCode.addCmd(asmOp, RBX, RAX);
        asmCode.addCmd(PUSH, RBX);
    }
}

void ExprArrayAccess::generate(AsmCode &asmCode) {
    generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RAX));
    asmCode.addCmd(PUSH, RAX);
}

SymTypeArrayPtr ExprArrayAccess::getTypeArraySymbol() {
    ExprIdentifierPtr identifier = getIdentifier();
    SymbolPtr typeSymbol = std::dynamic_pointer_cast<SymVar>(identifier->getSymbol())->getTypeSymbol();
    return std::dynamic_pointer_cast<SymTypeArray>(typeSymbol);
}

bool ExprArrayAccess::isLocal() {
    return ident->isLocal();
}

ExprRecordAccess::ExprRecordAccess(TokenPtr token, ExprPtr left,
                                   ExprPtr right) : ExprBinaryOp(token, left, right, NodeType::ExprRecordAccess) {}

void ExprRecordAccess::generateLValue(AsmCode &asmCode) {
    left->generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    AsmOpType asmOp; 
    if (!left->isLocal()) {
        asmOp = ADD;
    } else {
        asmOp = SUB; 
    }
    asmCode.addCmd(asmOp, RAX, std::dynamic_pointer_cast<ExprIdentifier>(right)->getSymbol()->getOffset());
    asmCode.addCmd(PUSH, RAX);
}

void ExprRecordAccess::generate(AsmCode &asmCode) {
    generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RAX));
    asmCode.addCmd(PUSH, RAX);
}

SymbolType ExprRecordAccess::getType() {
    return right->getType();
}

bool ExprRecordAccess::isLocal() {
    return left->isLocal();
}

StmtWhile::StmtWhile(ExprPtr expr, SyntaxNodePtr stmt): StmtNode(NodeType::StmtWhile), expr(expr), stmt(stmt) {}

std::string StmtWhile::getString(int depth) {
    std::stringstream sstream;
    sstream << getTreeString(depth, "while");
    sstream << expr->getString(depth + 1);
    sstream << stmt->getString(depth + 1);
    return sstream.str();
}

void StmtWhile::generate(AsmCode& asmCode) {
    std::string labelBody = asmCode.genLabelName();
    std::string labelCond = asmCode.genLabelName();
    std::string labelExit = asmCode.genLabelName();
    asmCode.addLabels(labelCond, labelExit);
    asmCode.addCmd(JMP, labelCond);
    asmCode.addLabel(labelBody);
    stmt->generate(asmCode);
    asmCode.addLabel(labelCond);
    expr->generate(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(TEST, RAX, RAX);
    asmCode.addCmd(JNZ, labelBody);
    asmCode.addLabel(labelExit);
    asmCode.deleteLabels();
}


StmtFor::StmtFor(SymbolPtr var, ExprPtr initExpr, ExprPtr finalExpr, SyntaxNodePtr stmt, bool isTo):
        StmtNode(NodeType::StmtFor), var(var), initExpr(initExpr), finalExpr(finalExpr), stmt(stmt), isTo(isTo) {}

std::string StmtFor::getString(int depth) {
    std::stringstream sstream;
    sstream << getTreeString(depth, "for " + var->getName());
    sstream << initExpr->getString(depth + 1);
    sstream << getTreeString(depth, isTo ? "to" : "downto");
    sstream << finalExpr->getString(depth + 1);
    sstream << stmt->getString(depth + 1);
    return sstream.str();
}

void StmtFor::generate(AsmCode& asmCode) {
    std::string labelCond = asmCode.genLabelName();
    std::string labelBody = asmCode.genLabelName();
    std::string labelInc  = asmCode.genLabelName();
    std::string labelExit = asmCode.genLabelName();
    asmCode.addLabels(labelInc, labelExit);
    var->generateLValue(asmCode);
    initExpr->generate(asmCode);
    asmCode.addCmd(POP, RBX);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOV, asmCode.getAdressOperand(RAX), RBX);
    asmCode.addCmd(JMP, labelCond);
    asmCode.addLabel(labelBody);
    stmt->generate(asmCode);
    asmCode.addLabel(labelInc);
    var->generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOV, RBX, asmCode.getAdressOperand(RAX));
    if (isTo) {
        asmCode.addCmd(ADD, RBX, 1);
    } else {
        asmCode.addCmd(SUB, RBX, 1);
    }
    asmCode.addCmd(MOV, asmCode.getAdressOperand(RAX), RBX);
    asmCode.addLabel(labelCond);
    generateCond(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(TEST, RAX, RAX);
    asmCode.addCmd(JNZ, labelBody);
    asmCode.addLabel(labelExit);
    asmCode.deleteLabels();
}

void StmtFor::generateCond(AsmCode& asmCode) {
    finalExpr->generate(asmCode);
    asmCode.addCmd(POP, RBX);
    var->generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RAX));
    asmCode.addCmd(CMP, RAX, RBX);
    std::string label1 = asmCode.genLabelName();
    std::string label2 = asmCode.genLabelName();
    if (isTo) {
        asmCode.addCmd(JLE, label1);
    } else {
        asmCode.addCmd(JGE, label1);
    }
    asmCode.addCmd(MOV, RAX, 0);
    asmCode.addCmd(JMP, label2);
    asmCode.addLabel(label1);
    asmCode.addCmd(MOV, RAX, 1);
    asmCode.addLabel(label2);
    asmCode.addCmd(PUSH, RAX);
}

StmtContinue::StmtContinue(): StmtNode(NodeType::StmtContinue) {}

std::string StmtContinue::getString(int depth) {
    return getTreeString(depth, "continue");
}

void StmtContinue::generate(AsmCode& asmCode) {
    std::string label = asmCode.getLabelContinue();
    if (!label.empty()) {
        asmCode.addCmd(JMP, label);
    }
}

StmtBreak::StmtBreak(): StmtNode(NodeType::StmtBreak) {}

std::string StmtBreak::getString(int depth) {
    return getTreeString(depth, "break");
}

void StmtBreak::generate(AsmCode& asmCode) {
    std::string label = asmCode.getLabelBreak();
    if (!label.empty()) {
        asmCode.addCmd(JMP, label);
    }
}

StmtIf::StmtIf(ExprPtr expr, SyntaxNodePtr thenStmt, SyntaxNodePtr elseStmt): StmtNode(NodeType::StmtIf), expr(expr),
                                                                              thenStmt(thenStmt), elseStmt(elseStmt) {}

std::string StmtIf::getString(int depth) {
    std::stringstream sstream;
    sstream << getTreeString(depth, "if");
    sstream << expr->getString(depth + 1);
    sstream << getTreeString(depth, "then");
    sstream << thenStmt->getString(depth + 1);
    if (elseStmt) {
        sstream << getTreeString(depth, "else");
        sstream << elseStmt->getString(depth + 1);
    }
    return sstream.str();
}

void StmtIf::generate(AsmCode &asmCode) {
    expr->generate(asmCode);
    std::string labelElse = asmCode.genLabelName();
    std::string labelEnd = asmCode.genLabelName();
    asmCode.addCmd(POP, RAX);
    asmCode.addCmd(TEST, RAX, RAX);
    asmCode.addCmd(JZ, labelElse);
    thenStmt->generate(asmCode);
    asmCode.addCmd(JMP, labelEnd);
    asmCode.addLabel(labelElse);
    if (elseStmt) {
        elseStmt->generate(asmCode);
    }
    asmCode.addLabel(labelEnd);
}

void StmtBlock::addStatment(SyntaxNodePtr stmt) {
    statments.push_back(stmt);
}

StmtBlock::StmtBlock(): SyntaxNode(NodeType::StmtBlock) {}

std::string StmtBlock::getString(int depth) {
    std::stringstream sstream;
    sstream << getTreeString(depth, "begin");
    for (auto stmt: statments) {
        sstream << stmt->getString(depth);
    }
    sstream << getTreeString(depth, "end");
    return sstream.str();
}

void StmtBlock::generate(AsmCode &asmCode) {
    for (auto stmt: statments) {
        stmt->generate(asmCode);
    }
}

NodeType SyntaxNode::getNodeType() {
    return type;
}

SyntaxNode::SyntaxNode(NodeType nodeType): type(nodeType) {}

std::string SyntaxNode::getTreeString(int depth, std::string str) {
    std::stringstream sstream;
    sstream << std::setw(spacesCount * depth)
            << std::string(std::max(depth == 0?0:1 * spacesCount - (int)str.size(), 0), '_') + str
            << std::endl;
    return sstream.str();
}

SymbolType SyntaxNode::getType() {
    return SymbolType::None;
}

void SyntaxNode::generate(AsmCode &asmCode) {

}

int SyntaxNode::getSize() {
    return 0;
}

StmtNode::StmtNode(NodeType nodeType): SyntaxNode(nodeType) {}

StmtEmpty::StmtEmpty(): StmtNode(NodeType::StmtEmpty) {}

std::string StmtEmpty::getString(int depth) {
    return "";
}

ExprCall::ExprCall(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes, SymbolPtr symbol):
        Expr(token, NodeType::ExprCall), nodes(nodes), ident(ident),
        symbol(std::dynamic_pointer_cast<SymProcBase>(symbol)) {}

std::string ExprCall::getString(int depth) {
    std::stringstream sstream;
    for (auto expr: nodes) {
        sstream << expr->getString(depth + 1);
    }
    sstream << Expr::getString(depth);
    sstream << ident->getString(depth + 1);
    return sstream.str();
}

void ExprCall::generate(AsmCode &asmCode) {
    int funcResultSize = 0;
    if (symbol->getType() == SymbolType::Func) {
        funcResultSize = symbol->getArgs()->getSymbol("result")->getSize();
        asmCode.addCmd(SUB, RSP, funcResultSize);
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (symbol->getArgs()->getSymbols()[i]->getType() == SymbolType::Param) {
            nodes[i]->generate(asmCode);
        } else {
            nodes[i]->generateLValue(asmCode);
        }
    }
    asmCode.addCmd(CALL, symbol->getName() + std::to_string(symbol->getLevel()));
    asmCode.addCmd(ADD, RSP, symbol->getArgs()->getSize() - funcResultSize);
}

SymbolType ExprCall::getType() {
    ident->getType();
}

ExprAssignOp::ExprAssignOp(TokenPtr token, ExprPtr left, ExprPtr right): ExprBinaryOp(token, left, right, NodeType::ExprAssignOp) {}

void ExprAssignOp::generate(AsmCode &asmCode) {
    right->generate(asmCode);
    left->generateLValue(asmCode);
    asmCode.addCmd(POP, RAX);
    if (left->getSize() <= 8) {
        asmCode.addCmd(POP, RBX);
        asmCode.addCmd(MOV, asmCode.getAdressOperand(RAX), RBX);
    } else {
        std::string labelBegin = asmCode.genLabelName();
        std::string labelEnd = asmCode.genLabelName();
        asmCode.addCmd(MOV, RBX, left->getSize());
        asmCode.addCmd(LEA, RAX, asmCode.getAdressOperand(RAX, left->getSize() - 8));
        asmCode.addLabel(labelBegin);
        asmCode.addCmd(CMP, RBX, 0);
        asmCode.addCmd(JLE, labelEnd);
        asmCode.addCmd(POP, RDX);
        asmCode.addCmd(MOV, asmCode.getAdressOperand(RAX), RDX);
        asmCode.addCmd(SUB, RAX, 8);
        asmCode.addCmd(SUB, RBX, 8);
        asmCode.addCmd(JMP, labelBegin);
        asmCode.addLabel(labelEnd);
    }
}

ExprWrite::ExprWrite(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes): ExprCall(token, ident, nodes) {}

void ExprWrite::generate(AsmCode &asmCode) {
    for (auto node: nodes) {
        switch (node->getType()) {
            case SymbolType::TypeInteger:
                node->generate(asmCode);
                asmCode.addWriteInt();
                break;
            case SymbolType::TypeFloat:
                node->generate(asmCode);
                asmCode.addWriteFloat();
                break;
            case SymbolType::TypeString:
                asmCode.addWriteString(node->getToken()->getValueStr());
        }
    }
}

ExprWriteln::ExprWriteln(TokenPtr token, ExprPtr ident, std::vector<ExprPtr> nodes): ExprWrite(token, ident, nodes) {}

void ExprWriteln::generate(AsmCode &asmCode) {
    ExprWrite::generate(asmCode);
    asmCode.addWriteNewLine();
}

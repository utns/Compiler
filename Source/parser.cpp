#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "parser.h"
#include "errors.h"
#include "optimizer.h"

Parser::Parser(const char* fileName): scanner(fileName),
    tokensName({
        {TokenType::Comma,                ","},
        {TokenType::Semicolon,            ";"},
        {TokenType::Colon,                ":"},
        {TokenType::OpeningParenthesis,   "("},
        {TokenType::ClosingParenthesis,   ")"},
        {TokenType::OpeningSquareBracket, "["},
        {TokenType::ClosingSquareBracket, "]"},
        {TokenType::DoubleDots,           ".."},
        {TokenType::Dot,                  "."},
        {TokenType::Add,                  "+"},
        {TokenType::Sub,                  "-"},
        {TokenType::Mul,                  "*"},
        {TokenType::Div,                  "/"},
        {TokenType::Assignment,           ":="},
        {TokenType::Equal,                "="},
        {TokenType::NotEqual,             "<>"},
        {TokenType::Less,                 "<"},
        {TokenType::LessEqual,            "<="},
        {TokenType::GreatEqual,           ">="},
        {TokenType::Great,                ">"},
        {TokenType::Hat,                  "^"},
        {TokenType::And,                  "and"},
        {TokenType::Array,                "array"},
        {TokenType::Begin,                "begin"},
        {TokenType::Break,                "break"},
        {TokenType::Case,                 "case"},
        {TokenType::Const,                "const"},
        {TokenType::Continue,             "continue"},
        {TokenType::DivRev,               "div"},
        {TokenType::Do,                   "do"},
        {TokenType::Downto,               "downto"},
        {TokenType::Else,                 "else"},
        {TokenType::End,                  "end"},
        {TokenType::Exit,                 "exit"},
        {TokenType::For,                  "for"},
        {TokenType::Function,             "function"},
        {TokenType::Goto,                 "goto"},
        {TokenType::If,                   "if"},
        {TokenType::Label,                "label"},
        {TokenType::Mod,                  "mod"},
        {TokenType::Nil,                  "nil"},
        {TokenType::Not,                  "not"},
        {TokenType::Of,                   "of"},
        {TokenType::Or,                   "or"},
        {TokenType::Procedure,            "procedure"},
        {TokenType::Program,              "program"},
        {TokenType::Record,               "record"},
        {TokenType::Repeat,               "repeat"},
        {TokenType::Set,                  "set"},
        {TokenType::Shl,                  "shl"},
        {TokenType::Shr,                  "shr"},
        {TokenType::Then,                 "then"},
        {TokenType::To,                   "to"},
        {TokenType::Type,                 "type"},
        {TokenType::Until,                "until"},
        {TokenType::Var,                  "var"},
        {TokenType::While,                "while"},
        {TokenType::Xor,                  "xor"},
        {TokenType::Identifier,           "identifier"},
    }),
    symbolsName({
        {SymbolType::VarParam, "var param"},
        {SymbolType::VarConst, "var const"},
        {SymbolType::VarLocal, "var local"},
        {SymbolType::VarGlobal, "var global"},
        {SymbolType::TypeFloat, "type float"},
        {SymbolType::TypeInteger, "type integer"},
        {SymbolType::TypeArray, "type array"},
        {SymbolType::TypePointer, "type pointer"},
        {SymbolType::TypeRecord, "type record"},
        {SymbolType::TypeAlias, "type alias"},
        {SymbolType::TypeSubrange, "type subrange"},
        {SymbolType::Proc, "proc"}, 
        {SymbolType::ConstInteger, "const integer"},
        {SymbolType::ConstFloat, "const float"},
    }),
    procGenCount(0)
{
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

    tablesStack.addTable(SymTablePtr(new SymTable()));
    tablesStack.top()->addSymbol(SymbolPtr(new SymTypeInteger));
    tablesStack.top()->addSymbol(SymbolPtr(new SymTypeFloat));
    tablesStack.top()->addSymbol(SymbolPtr(new SymTypeChar));
}

void Parser::parse() {
    scanner.nextToken();
    parseDeclaration(0, true);
    checkTokenType(scanner.getToken(), TokenType::Begin);
    root = parseStmt();
    checkTokenType(scanner.getToken(), TokenType::Dot);
}

void Parser::parseExpr() {
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
        case TokenType::FloatNumber:
            return ExprPtr(new ExprReal(token));
        case TokenType::String:
            return ExprPtr(new ExprString(token));
        case TokenType::OpeningParenthesis:
            expr = parseExpr(0);
            checkTokenType(scanner.getToken(), TokenType::ClosingParenthesis);
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

bool Parser::checkTokenType(TokenPtr token, TokenType expectedType) {
    if (token->getType() != expectedType) {
        throw ExpectedError(token->getLine(), token->getPos(), tokensName[expectedType],
                            scanner.getToken()->getValueStr());
    }
    return true;
}

bool Parser::checkExprType(ExprPtr expr, SymbolType expectedType) {
    SymbolType type = expr->getType();
    if (type != expectedType) {
        throw ExpectedError(expr->getToken()->getLine(), expr->getToken()->getPos(), symbolsName[expectedType], 
                            symbolsName[type]); 
    }
    return  true; 
}

std::vector<ExprPtr> Parser::getArgsArray(TokenType closingType) {
    std::vector<ExprPtr> indexes;
    if (scanner.getToken()->getType() != closingType) {
        indexes.push_back(parseExpr(0));
    }
    while (scanner.getToken()->getType() != closingType) {
        checkTokenType(scanner.getToken(), TokenType::Comma);
        TokenPtr token = scanner.getToken();
        if (scanner.getNextToken()->getType() == closingType) {
            throw ExpectedError(token->getLine(), token->getPos(), tokensName[closingType], token->getValueStr());
        };
        indexes.push_back(parseExpr(0));
    }
    scanner.nextToken();
//    std::reverse(indexes.begin(), indexes.end());
    return indexes;
}

ExprPtr Parser::parseIdentifier(TokenPtr token) {
    ExprPtr left(new ExprIdentifier(token, tablesStack.getSymbol(token)));
    switch (scanner.getToken()->getType()) {
        case TokenType::OpeningSquareBracket:
            left = parseArrayAccess(left);
            break;
        case TokenType::OpeningParenthesis:
            left = parseCall(left);
            if (scanner.getToken()->getType() == TokenType::OpeningSquareBracket) {
                left = parseArrayAccess(left);
            }
            break;
    }
    TokenPtr dotToken = scanner.getToken();
    while (dotToken->getType() == TokenType::Dot) {
        checkTokenType(scanner.getNextToken(), TokenType::Identifier);
        token = scanner.getToken();
        scanner.nextToken();
        if (left->getNodeType() == NodeType::ExprRecordAccess) {
            ExprRecordAccessPtr recordAccess = std::dynamic_pointer_cast<ExprRecordAccess>(left);
            SymTablePtr table;// = getTable(std::dynamic_pointer_cast<ExprIdentifier>(recordAccess->getLeft()));
            if (recordAccess->getLeft()->getNodeType() == NodeType::ExprArrayAccess) {
                SymbolPtr refSymbol = std::dynamic_pointer_cast<ExprArrayAccess>(recordAccess->getLeft())->getRefSymbol();
                checkSymbolType(refSymbol, SymbolType::TypeRecord, token);
                table = std::dynamic_pointer_cast<SymTypeRecord>(refSymbol)->getTable();
            } else if (recordAccess->getLeft()->getNodeType() == NodeType::ExprIdentifier) {
                ExprIdentifierPtr identifier = std::dynamic_pointer_cast<ExprIdentifier>(recordAccess->getLeft());
                table = getTable(identifier);
            }
            checkExprType(recordAccess->getRight(), SymbolType::TypeRecord);
            SymbolPtr symbol = table->getSymbol(recordAccess->getRight()->getToken());
            SymbolPtr typeSymbol = std::dynamic_pointer_cast<SymVar>(symbol)->getTypeSymbol();
            SymbolPtr type = std::dynamic_pointer_cast<SymTypeAlias>(typeSymbol)->getRefSymbol();
            table = std::dynamic_pointer_cast<SymTypeRecord>(type)->getTable();
            left = ExprPtr(new ExprRecordAccess(dotToken, left, ExprPtr(new ExprIdentifier(token, table->getSymbol(token)))));
        } else if (left->getNodeType() == NodeType::ExprArrayAccess) {
            SymbolPtr refSymbol = std::dynamic_pointer_cast<ExprArrayAccess>(left)->getRefSymbol();
            checkSymbolType(refSymbol, SymbolType::TypeRecord, token);
            SymTablePtr table = std::dynamic_pointer_cast<SymTypeRecord>(refSymbol)->getTable();
            left = ExprPtr(new ExprRecordAccess(dotToken, left, ExprPtr(new ExprIdentifier(token, table->getSymbol(token)))));
        } else if (left->getNodeType() == NodeType::ExprIdentifier) {
            ExprIdentifierPtr identifier = std::dynamic_pointer_cast<ExprIdentifier>(left);
            SymTablePtr table = getTable(identifier);
//            std::cout << token->getText() << " " << symbolsName[table->getSymbol(token)->getType()] << std::endl;
            left = ExprPtr(new ExprRecordAccess(dotToken, left, ExprPtr(new ExprIdentifier(token, table->getSymbol(token)))));
        } else {
            left = ExprPtr(new ExprRecordAccess(dotToken, left,
                                                ExprPtr(new ExprIdentifier(token, tablesStack.getSymbol(token)))));
        }
        left = parseArrayAccess(left);
        dotToken = scanner.getToken();
    }
    return left;
}

SymTablePtr Parser::getTable(ExprIdentifierPtr identifier) {
    checkExprType(identifier, SymbolType::TypeRecord);
    SymbolPtr typeSymbol = std::dynamic_pointer_cast<SymVar>(identifier->getSymbol())->getTypeSymbol();
    SymbolPtr type = std::dynamic_pointer_cast<SymTypeAlias>(typeSymbol)->getRefSymbol();
    return  std::dynamic_pointer_cast<SymTypeRecord>(type)->getTable();
}

std::string Parser::getTreeString() {
    std::stringstream sstream;
    try {
        parse();
        for (auto body: proceduresBody) {
            sstream << body.second->getString(0) << std::endl;
        }
        sstream << root->getString(0);
    } catch (BaseError& error) {
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

ExprPtr Parser::parseArrayAccess(ExprPtr left) {
    TokenPtr tokenOpen = scanner.getToken();
    if (tokenOpen->getType() == TokenType::OpeningSquareBracket) {
        TokenPtr token = scanner.getNextToken();
        if (token->getType() == TokenType::ClosingSquareBracket) {
            throw IllegalExpression(token->getLine(), token->getPos());
        }
        std::vector<ExprPtr> indexes = getArgsArray(TokenType::ClosingSquareBracket);
        left = ExprPtr(new ExprArrayAccess(tokenOpen, left, indexes));
    }
    return left;
}

ExprPtr Parser::parseCall(ExprPtr left) {
    TokenPtr token = scanner.getToken();
    if (token->getType() == TokenType::OpeningParenthesis) {
        scanner.nextToken();
        std::vector<ExprPtr> indexes = getArgsArray(TokenType::ClosingParenthesis);
        if (left->getToken()->getText() == "writeln") {
            left = ExprPtr(new ExprWriteln(token, left, indexes));
        } else if (left->getToken()->getText() == "write") {
            left = ExprPtr(new ExprWrite(token, left, indexes));
        } else {
            left = ExprPtr(new ExprCall(token, left, indexes, tablesStack.getSymbol(left->getToken())));
//            left = ExprPtr(new ExprCall(token, left, indexes));
        }
    }
    return left;
}

SyntaxNodePtr Parser::parseStmt() {
    TokenPtr token = scanner.getToken();
    if (token->getType() == TokenType::Identifier) {
        return parseStmtIdentifier();
    }
    scanner.nextToken();
    switch (token->getType()) {
        case TokenType::Begin:
            return parseBlock();
        case TokenType::If:
            return parseIf();
        case TokenType::While:
            return parseWhile();
        case TokenType::For:
            return parseFor();
        case TokenType::Semicolon:
            return parseEmpty();
        case TokenType::Continue:
            return parseContinue();
        case TokenType::Break:
            return parseBreak();
        default:
            return parseEmpty();
    }
}

SyntaxNodePtr Parser::parseStmtIdentifier() {
    ExprPtr expr = parseExpr(0);
    TokenPtr token = scanner.getToken();
    if (token->getType() == TokenType::Assignment) {
        scanner.nextToken();
        return SyntaxNodePtr(new ExprAssignOp(token, expr, parseExpr(0)));
    } else {
        if (expr->getNodeType() != NodeType::ExprCall) {
            throw IllegalExpression(expr->getToken()->getLine(), expr->getToken()->getLine());
        }
        return expr;
    }
}

SyntaxNodePtr Parser::parseIf() {
    ExprPtr expr = parseExpr(0);
    checkTokenType(scanner.getToken(), TokenType::Then);
    scanner.nextToken();
    SyntaxNodePtr thenStmt = parseStmt();
    SyntaxNodePtr elseStmt;
    if (scanner.getToken()->getType() == TokenType::Else) {
        scanner.nextToken();
        elseStmt = parseStmt();
    }
    return SyntaxNodePtr(new StmtIf(expr, thenStmt, elseStmt));
}

SyntaxNodePtr Parser::parseWhile() {
    ExprPtr expr = parseExpr(0);
    checkTokenType(scanner.getToken(), TokenType::Do);
    scanner.nextToken();
    return SyntaxNodePtr(new StmtWhile(expr, parseStmt()));
}

SyntaxNodePtr Parser::parseFor() {
    checkTokenType(scanner.getToken(), TokenType::Identifier);//        std::cout << "----------------------" << std::endl;
//        std::cout << parser.getRoot()->getString(0) << std::endl;
//        std::cout << "----------------------" << std::endl;
    SymbolPtr var = tablesStack.getSymbol(scanner.getToken());
    checkTokenType(scanner.getNextToken(), TokenType::Assignment);
    scanner.nextToken();
    ExprPtr initExpr = parseExpr(0);
    TokenPtr token = scanner.getToken();
    if (token->getType() != TokenType::To && token->getType() != TokenType::Downto) {
        throw ExpectedError(token->getLine(), token->getPos(), tokensName[TokenType::To] + "/" + tokensName[TokenType::Downto],
                            token->getValueStr());
    }
    bool isTo = token->getType() == TokenType::To;
    scanner.nextToken();
    ExprPtr finalExpr = parseExpr(0);
    checkTokenType(scanner.getToken(), TokenType::Do);
    scanner.nextToken();
    return SyntaxNodePtr(new StmtFor(var, initExpr, finalExpr, parseStmt(), isTo));
}


SyntaxNodePtr Parser::parseBlock() {
    std::shared_ptr<StmtBlock> block(new StmtBlock());
    while (scanner.getToken()->getType() != TokenType::End && scanner.getToken()->getType() != TokenType::EndOfFile 
           && scanner.getToken()->getType() != TokenType::Dot) {
        SyntaxNodePtr stmt = parseStmt();
        if (stmt->getNodeType() == NodeType::StmtEmpty) {
            continue;
        }
        block->addStatment(stmt);
        if (scanner.getToken()->getType() == TokenType::Semicolon) {
            scanner.nextToken();
        } else {
            checkTokenType(scanner.getToken(), TokenType::End);
        }
    }
    checkTokenType(scanner.getToken(), TokenType::End);
    scanner.nextToken();
    return block;
}

void Parser::parseDeclaration(int level, bool isGlobal) {
    while (isDeclaration(scanner.getToken()->getType())) {
        TokenPtr token = scanner.getToken();
        scanner.nextToken();
        switch (token->getType()) {
            case TokenType::Var:
                parseVarDeclaration(isGlobal);
                break;
            case TokenType::Const:
                parseConstDeclaration();
                break;
            case TokenType::Type:
                parseTypeDeclaration();
                break;
            case TokenType::Procedure:
                parseProcDeclaration(level);
                break;
            case TokenType::Function:
                parseFuncDeclaration(level);
                break;
        }
    }
    addProcSymbol("write");
    addProcSymbol("writeln");
}

void Parser::parseVarDeclaration(bool isGlobal) {
    std::vector<TokenPtr> identifiers;
    TokenPtr token = scanner.getToken();
    checkTokenType(token, TokenType::Identifier);
    while (token->getType() == TokenType::Identifier) {
        identifiers.push_back(token);
        if (scanner.getNextToken()->getType() == TokenType::Colon) {
            scanner.nextToken();
            SymbolPtr type = parseType();
            checkTokenType(scanner.getToken(), TokenType::Semicolon);
            token = scanner.getNextToken();
            for (auto identifier: identifiers) {
                tablesStack.top()->checkUnique(identifier);
                if (isGlobal) {
                    tablesStack.top()->addSymbol(SymbolPtr(new SymVarGlobal(identifier->getText(), type)));
                } else {
                    tablesStack.top()->addSymbol(SymbolPtr(new SymVarLocal(identifier->getText(), type)));
                }
            }
            identifiers.clear();
        } else {
            checkTokenType(scanner.getToken(), TokenType::Comma);
            token = scanner.getNextToken();
            checkTokenType(token, TokenType::Identifier);
        }
    }
    return;
}

SymbolPtr Parser::parseType() {
    TokenPtr token = scanner.getToken();
    SymbolPtr type;
    switch (token->getType()) {
        case TokenType::Identifier:
            if (tablesStack.getSymbol(token)->isType()) {
                type = tablesStack.getSymbol(token);
                scanner.nextToken();
                break;
            }
        default:
            type = parseSubrange();
            break;
        case TokenType::Record:
            scanner.nextToken();
            type = parseRecord();
            break;
        case TokenType::Hat:
            scanner.nextToken();
            type = parsePointer();
            break;
        case TokenType::Array:
            scanner.nextToken();
            type = parseArray();
            break;
    }
    return type;
}

void Parser::parseConstDeclaration() {
    checkTokenType(scanner.getToken(), TokenType::Identifier);
    while (scanner.getToken()->getType() == TokenType::Identifier) {
        std::string identifier = scanner.getToken()->getText();
        tablesStack.top()->checkUnique(scanner.getToken());
        checkTokenType(scanner.getNextToken(), TokenType::Equal);
        scanner.nextToken();
        tablesStack.top()->addSymbol(parseConst(identifier));
        checkTokenType(scanner.getToken(), TokenType::Semicolon);
        scanner.nextToken();
    }
}

bool Parser::isDeclaration(TokenType type) {
    return type == TokenType::Const || type == TokenType::Var || type == TokenType::Type
            || type == TokenType::Procedure || type == TokenType::Function;
}

void Parser::parseTypeDeclaration() {
    checkTokenType(scanner.getToken(), TokenType::Identifier);
    while (scanner.getToken()->getType() == TokenType::Identifier) {
        std::string identifier = scanner.getToken()->getText();
        tablesStack.top()->checkUnique(scanner.getToken());
        checkTokenType(scanner.getNextToken(), TokenType::Equal);
        scanner.nextToken();
        SymbolPtr type = parseType();
        if (type->getType() == SymbolType::TypeAlias) {
            type = std::dynamic_pointer_cast<SymTypeAlias>(type)->getRefSymbol();
        }
        tablesStack.top()->addSymbol(SymbolPtr(new SymTypeAlias(type, identifier)));
        checkTokenType(scanner.getToken(), TokenType::Semicolon);
        scanner.nextToken();
    }
}

SymbolPtr Parser::parsePointer() {
    TokenPtr token = scanner.getToken();
    checkTokenType(token, TokenType::Identifier);
    scanner.nextToken();
    SymbolPtr refType = tablesStack.getSymbol(token);
    return SymbolPtr(new SymTypePointer(refType));
}


SymbolPtr Parser::parseSubrange() {
    TokenPtr token = scanner.getToken();
    if (token->getType() == TokenType::Identifier 
            && tablesStack.haveSymbol(token->getText()) 
            && tablesStack.getSymbol(token)->getType() == SymbolType::TypeAlias 
            && std::dynamic_pointer_cast<SymTypeAlias>(tablesStack.getSymbol(token))->getRefSymbol()->getType()
               == SymbolType::TypeSubrange) {
        scanner.nextToken();
        return std::dynamic_pointer_cast<SymTypeAlias>(tablesStack.getSymbol(token))->getRefSymbol();
    }
    SymbolPtr left = parseConst();
    checkSymbolType(left, SymbolType::ConstInteger, token);
    checkTokenType(scanner.getToken(), TokenType::DoubleDots);
    token = scanner.getNextToken();
    SymbolPtr right = parseConst();
    checkSymbolType(right, SymbolType::ConstInteger, token);
    return SymbolPtr(new SymTypeSubrange(
            std::dynamic_pointer_cast<SymIntegerConst>(left)->getValue(),
            std::dynamic_pointer_cast<SymIntegerConst>(right)->getValue()));
}

SymbolPtr Parser::parseConst(std::string identifier) {
    TokenPtr token = scanner.getToken();
    scanner.nextToken();
    if (token->getType() == TokenType::IntegerNumber) {
        return SymbolPtr(new SymIntegerConst(identifier, std::dynamic_pointer_cast<IntegerNumber>(token)->getValue()));
    } else if (token->getType() == TokenType::FloatNumber) {
        return SymbolPtr(new SymFloatConst(identifier, std::dynamic_pointer_cast<FloatNumber>(token)->getValue()));
    } else if (token->getType() == TokenType::Identifier) {
        SymbolPtr symbol = tablesStack.getSymbol(token);
        if (symbol->getType() == SymbolType::ConstInteger) {
            return SymbolPtr(new SymIntegerConst(identifier,
                    std::dynamic_pointer_cast<SymIntegerConst>(symbol)->getValue()));
        } else if (symbol->getType() == SymbolType::ConstFloat) {
            return SymbolPtr(new SymFloatConst(identifier,
                    std::dynamic_pointer_cast<SymFloatConst>(symbol)->getValue()));
        } else {
            throw IncorrectConst(symbol->getName());
        }
    } else {
        throw IncorrectConst(token->getText(), token->getLine(), token->getPos());
    }
}

bool Parser::checkSymbolType(SymbolPtr symbol, SymbolType expectedType, TokenPtr token) {
    if (symbol->getType() != expectedType) {
        throw ExpectedError(token->getLine(), token->getPos(), symbolsName[expectedType], symbolsName[symbol->getType()]);
    }
    return true;
}

SymbolPtr Parser::parseRecord() {
    tablesStack.addTable(SymTablePtr(new SymTable()));
    parseVarDeclaration(true);
    SymbolPtr record = SymbolPtr(new SymTypeRecord(tablesStack.top()));
    tablesStack.pop();
    checkTokenType(scanner.getToken(), TokenType::End);
    scanner.nextToken();
    return record;
}

SymbolPtr Parser::parseArray() {
    if (scanner.getToken()->getType() == TokenType::OpeningSquareBracket) {
        scanner.nextToken();
        SymbolPtr subrange = parseSubrange();
        checkTokenType(scanner.getToken(), TokenType::ClosingSquareBracket);
        checkTokenType(scanner.getNextToken(), TokenType::Of);
        scanner.nextToken();
        return SymbolPtr(new SymTypeArray(parseType(), std::dynamic_pointer_cast<SymTypeSubrange>(subrange)->getLeft(),
                                                       std::dynamic_pointer_cast<SymTypeSubrange>(subrange)->getRight()));
    } else {
        checkTokenType(scanner.getToken(), TokenType::Of);
        scanner.nextToken();
        return SymbolPtr(new SymTypeOpenArray(parseType()));
    }
}


std::string Parser::getDeclString() {
    std::stringstream sstream;
    try {
        sstream << getSymTableString();
    } catch (BaseError& error) {
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

std::string Parser::getSymTableString() {
    return tablesStack.top()->getString(0);
}

SyntaxNodePtr Parser::parseEmpty() {
    return SyntaxNodePtr(new StmtEmpty());
}

SyntaxNodePtr Parser::parseContinue() {
    checkTokenType(scanner.getToken(), TokenType::Semicolon);
    return SyntaxNodePtr(new StmtContinue());
}

SyntaxNodePtr Parser::parseBreak() {
    checkTokenType(scanner.getToken(), TokenType::Semicolon);
    return SyntaxNodePtr(new StmtBreak());
}

void Parser::parseProcDeclaration(int level) {
    std::string name = scanner.getToken()->getText();
    tablesStack.top()->checkUnique(scanner.getToken());
    scanner.nextToken();
    SymbolPtr proc(new SymProc(name));
    tablesStack.top()->addSymbol(proc);
    tablesStack.addTable(SymTablePtr(new SymTable));
    std::dynamic_pointer_cast<SymProcBase>(proc)->setArgs(parseParams(proc));
    checkTokenType(scanner.getToken(), TokenType::Semicolon);
    scanner.nextToken();
    std::dynamic_pointer_cast<SymProcBase>(proc)->setLocals(parseProcBody(proc, level + 1));
    std::dynamic_pointer_cast<SymProcBase>(proc)->setLevel(level);
    tablesStack.pop();
}

void Parser::parseFuncDeclaration(int level) {
    std::string name = scanner.getToken()->getText();
    tablesStack.top()->checkUnique(scanner.getToken());
    scanner.nextToken();
    SymbolPtr func(new SymFunc(name));
    tablesStack.top()->addSymbol(func);
    tablesStack.addTable(SymTablePtr(new SymTable));
    parseParams(func);
    checkTokenType(scanner.getToken(), TokenType::Colon);
    scanner.nextToken();
    tablesStack.top()->addSymbol(SymbolPtr(new SymFuncResult("result", parseType(), func)));
    checkTokenType(scanner.getToken(), TokenType::Semicolon);
    std::dynamic_pointer_cast<SymProcBase>(func)->setArgs(tablesStack.top());
    scanner.nextToken();
    std::dynamic_pointer_cast<SymProcBase>(func)->setLocals(parseProcBody(func, level + 1));
    std::dynamic_pointer_cast<SymProcBase>(func)->setLevel(level);
    tablesStack.pop();
}

SymTablePtr Parser::parseParams(SymbolPtr proc) {
    checkTokenType(scanner.getToken(), TokenType::OpeningParenthesis);
    TokenPtr token = scanner.getNextToken();
    int offset = 0;
    while (token->getType() == TokenType::Identifier || token->getType() == TokenType::Var) {
        bool isVar = token->getType() == TokenType::Var;
        TokenPtr identifier = token;
        std::vector<TokenPtr> identifiers;
        scanner.nextToken();
        if (!isVar) {
            if (scanner.getToken()->getType() != TokenType::Colon) {
                scanner.nextToken();
                identifiers = parseIdentifiers();
            }
            identifiers.push_back(identifier);
        } else {
            identifiers = parseIdentifiers();
        }
        checkTokenType(scanner.getToken(), TokenType::Colon);
        scanner.nextToken();
        SymbolPtr type = parseType();
        for (int i = 0; i < identifiers.size(); ++i) {
            TokenPtr identifier = i == 0 ? identifiers.back() : identifiers[i - 1];
            tablesStack.top()->checkUnique(identifier);
            offset += type->getSize(); 
//            std::cout << identifier->getText() << " " << offset << std::endl;
            if (isVar) {
                tablesStack.top()->addSymbol(SymbolPtr(new SymVarParam(identifier->getText(), type, proc, 0)));
            } else {
                tablesStack.top()->addSymbol(SymbolPtr(new SymParam(identifier->getText(), type, proc, 0)));
            }
        }
        if (scanner.getToken()->getType() != TokenType::Semicolon) {
            checkTokenType(scanner.getToken(), TokenType::ClosingParenthesis);
            break;
        } else {
            token = scanner.getNextToken();
        }
    }
    int size = tablesStack.top()->getSize();
//    std::cout << size << std::endl;
    for (auto symbol: tablesStack.top()->getSymbols()) {
        symbol->setOffset(size - symbol->getOffset());
//        std::cout << symbol->getName() << " " << symbol->getOffset() << std::endl;
    }
    scanner.nextToken();
    return tablesStack.top();
}

std::vector<TokenPtr> Parser::parseIdentifiers() {
    TokenPtr token = scanner.getToken();
    checkTokenType(token, TokenType::Identifier);
    std::vector<TokenPtr> identifiers = {token};
    while (scanner.getNextToken()->getType() == TokenType::Comma) {
        token = scanner.getNextToken();
        checkTokenType(token, TokenType::Identifier);
        identifiers.push_back(token);
    }
    return identifiers;
}

SymTablePtr Parser::parseProcBody(SymbolPtr proc, int level) {
    tablesStack.addTable(SymTablePtr(new SymTable()));
    parseDeclaration(level, false);
    checkTokenType(scanner.getToken(), TokenType::Begin);
    scanner.nextToken();
//    proceduresBody.push_back(parseBlock());
    proceduresBody[proc] = parseBlock();
    checkTokenType(scanner.getToken(), TokenType::Semicolon);
    scanner.nextToken();
    SymTablePtr locals = tablesStack.top();
    tablesStack.pop();
    return locals;
}

std::string Parser::getExprTreeString() {
    std::stringstream sstream;
    try {
        parseExpr();
        sstream << root->getString(0);
    } catch (BaseError& error) {
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

std::string Parser::getDeclTestString() {
    std::stringstream sstream;
    try {
        scanner.nextToken();
        parseDeclaration(0, true);
        sstream << getSymTableString();
    } catch (BaseError& error) {
        sstream << error.what() << std::endl;
    }
    return sstream.str();
}

SyntaxNodePtr Parser::getRoot() {
    return root;
}

std::string Parser::getAsmString() {
    Optimizer optimizer(asmCode);
    optimizer.optimize();
    return asmCode.getString();
}

void Parser::generateAsmCode() {
    for (auto symbol: tablesStack.top()->getSymbols()) {
//        std::cout << symbol->getName() << std::endl;
        symbol->generateDecl(asmCode);
        if ((symbol->getType() == SymbolType::Proc || symbol->getType() == SymbolType::Func)
            && symbol->getName() != "write" && symbol->getName() != "writeln"){
            generateProc(symbol, 0);
        }
    }
    asmCode.addLabel("main");
    root->generate(asmCode);
}

void Parser::addProcSymbol(std::string name) {
    SymbolPtr proc(new SymProc(name));
    tablesStack.top()->addSymbol(proc);
    SymTablePtr table(new SymTable);
    std::dynamic_pointer_cast<SymProcBase>(proc)->setArgs(table);
    std::dynamic_pointer_cast<SymProcBase>(proc)->setLocals(table);
}

void Parser::generateProc(SymbolPtr symbol, int level) {
    SymProcBasePtr proc = std::dynamic_pointer_cast<SymProcBase>(symbol);
    asmCode.addLabel(symbol->getName() + std::to_string(proc->getLevel()));
    asmCode.addCmd(PUSH, RBP);
    asmCode.addCmd(MOV, RBP, RSP);
    asmCode.addCmd(SUB, RSP, proc->getLocals()->getSize());
    proceduresBody[symbol]->generate(asmCode);
    asmCode.addCmd(MOV, RSP, RBP);
    asmCode.addCmd(POP, RBP);
    asmCode.addCmd(RET);
    for (auto symbol: proc->getLocals()->getSymbols()) {
        if ((symbol->getType() == SymbolType::Proc || symbol->getType() == SymbolType::Func)
            && symbol->getName() != "write" && symbol->getName() != "writeln"){
            generateProc(symbol, level + 1);
        }
    }
}
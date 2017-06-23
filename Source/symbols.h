#pragma once

#include <string>
#include <memory>
#include <map>
#include <stack>
#include <vector>
#include "token.h"
#include "asmgen.h"

enum class SymbolType {
    FuncResult,
    VarParam,
    Param,
    VarConst,
    VarLocal,
    VarGlobal,
    TypeFloat,
    TypeInteger,
    TypeChar,
    TypeArray,
    TypeOpenArray,
    TypePointer,
    TypeRecord,
    TypeAlias,
    TypeSubrange,
    TypeString,
    Proc,
    Func,
    ConstInteger,
    ConstFloat,
    None,
};

class Symbol {
    public:
        Symbol(SymbolType type, std::string name, int size = 0);
        virtual std::string getName();
        virtual SymbolType getType();
        virtual std::string getString(int depth);
        virtual bool isType();
        virtual int getSize();
        virtual void generateDecl(AsmCode &asmCode);
        virtual void generateLValue(AsmCode &asmCode);
        virtual void generateValue(AsmCode &asmCode);
        virtual void generate(AsmCode &asmCode, int level = 0);
        virtual void setOffset(int offset);
        virtual int getOffset();
        virtual SymbolType getVarType();
    protected:
        int offset;
        int size;
        SymbolType type;
        std::string name;
        static const int spacesCount = 5;
        static const int columnWidth1 = 15;
        static const int columnWidth2 = 15;
        static const int columnWidth3 = 15;
};

typedef std::shared_ptr<Symbol> SymbolPtr;

class SymTable {
    public:
        void addSymbol(SymbolPtr symbol);
        bool haveSymbol(std::string name);
        SymbolPtr getSymbol(TokenPtr token);
        SymbolPtr getSymbol(std::string name);
        std::string getString(int depth);
        void checkUnique(TokenPtr token);
        std::vector<SymbolPtr> getSymbols();
        int getSize();
    private:
        int size = 0;
        std::vector<SymbolPtr> symbols;
        std::map<std::string, int> symbolsName;
};

typedef std::shared_ptr<SymTable> SymTablePtr;

class SymStack {
    public:
        void addTable(SymTablePtr table);
        SymTablePtr top();
        void pop();
        SymTablePtr findTable(std::string symbol);
        bool haveSymbol(std::string name);
        SymbolPtr getSymbol(TokenPtr token);
    private:
        std::vector<SymTablePtr> tables;
};

typedef std::shared_ptr<SymStack> SymStackPtr;

class SymType: public Symbol {
    public:
        SymType(SymbolType type, std::string name, int size = 0);
        std::string getString(int depth);
        bool isType();
        int getSize() override;
};

typedef std::shared_ptr<SymType> SymTypePtr;

class SymVar: public Symbol {
    public:
        SymVar(SymbolType type, std::string name, SymbolPtr varType);
        std::string getTypeName();
        SymbolType getVarType() override;
        SymbolPtr getTypeSymbol();
        int getSize() override;
    protected:
        void generateMemoryCopy(AsmCode &asmCode, AsmCmdPtr cmdMemory, AsmOpType opType);
        SymbolPtr varType;
};

class SymParamBase: public SymVar {
    public:
        SymParamBase(SymbolType type, std::string name, SymbolPtr varType, SymbolPtr method, int offset);
    protected:
        SymbolPtr method;
//        int offset;
};

class SymParam: public SymParamBase {
    public:
        SymParam(std::string name, SymbolPtr varType, SymbolPtr method, int offset);
        std::string getString(int depth) override;
        void generateLValue(AsmCode &asmCode) override;
        void generateValue(AsmCode &asmCode) override;
};

class SymVarParam: public SymParamBase {
    public:
        SymVarParam(std::string name, SymbolPtr varType, SymbolPtr method, int offset);
        std::string getString(int depth) override;
        void generateLValue(AsmCode &asmCode) override;
        void generateValue(AsmCode &asmCode) override;
        int getSize() override;
};

class SymFuncResult: public SymParamBase {
    public:
        SymFuncResult(std::string name, SymbolPtr varType, SymbolPtr method);
        std::string getString(int depth) override;
        void generateLValue(AsmCode &asmCode) override;
        void generateValue(AsmCode &asmCode) override;
};

class SymVarConst: public SymVar {
    public:
        SymVarConst(std::string name, SymbolPtr varType);
};

class SymVarLocal: public SymVar {
    public:
        SymVarLocal(std::string name, SymbolPtr varType);
        void generateLValue(AsmCode &asmCode) override;
        void generateValue(AsmCode &asmCode) override;
};

class SymVarGlobal: public SymVar {
    public:
        SymVarGlobal(std::string name, SymbolPtr varType);
        std::string getString(int depth);
        void generateDecl(AsmCode &asmCode) override;
        void generateLValue(AsmCode &asmCode) override;
        void generateValue(AsmCode &asmCode) override;
};

class SymTypeFloat: public SymType {
    public:
        SymTypeFloat();
};

class SymTypeInteger: public SymType {
    public:
        SymTypeInteger();
};

class SymTypeChar: public SymType {
    public:
        SymTypeChar();
};

class SymTypeArray: public SymType {
    public:
        SymTypeArray(SymbolPtr elemType, int left, int right);
        void setElemType(SymbolPtr elemType);
        std::string getName();
        SymbolType getElemType();
        SymbolPtr getElemSybmol();
        int getSize() override;
        int getLowRange();
    private:
        SymbolPtr elemType;
        int left, right;
};

typedef std::shared_ptr<SymTypeArray> SymTypeArrayPtr;

class SymTypeOpenArray: public SymType {
    public:
        SymTypeOpenArray(SymbolPtr elemType);
    private:
        SymbolPtr elemType;
};

class SymTypePointer: public SymType {
    public:
        SymTypePointer(SymbolPtr refType);
        std::string getName() override ;
    private:
        SymbolPtr refType;
};

class SymTypeAlias: public SymType {
    public:
        SymTypeAlias(SymbolPtr refType, std::string name);
        std::string getString(int depth);
        SymbolPtr getRefSymbol();
        SymbolType getRefType();
        int getSize() override;
    private:
        SymbolPtr refType;
};

typedef std::shared_ptr<SymTypeAlias> SymTypeAliasPtr;

class SymTypeRecord: public SymType {
    public:
        SymTypeRecord(SymTablePtr symTable);
        std::string getString(int depth);
        SymTablePtr getTable();
        int getSize() override;
    private:
        SymTablePtr symTable;
};

typedef std::shared_ptr<SymTypeRecord> SymbolRecordPtr;

class SymTypeSubrange: public SymType {
    public:
        SymTypeSubrange(int left, int right);
        int getLeft();
        int getRight();
    private:
        int left, right;
};

class SymProcBase: public Symbol {
    public:
        SymProcBase(SymbolType type, std::string name);
        void setArgs(SymTablePtr args);
        void setLocals(SymTablePtr locals);
        std::string getString(int depth);
        SymTablePtr getArgs();
        SymTablePtr getLocals();
        void setLevel(int level);
        int getLevel();
    protected:
        int level;
        SymTablePtr args, locals;
};

typedef std::shared_ptr<SymProcBase> SymProcBasePtr;

class SymProc: public SymProcBase {
    public:
        SymProc(std::string name);
        std::string getString(int depth) override;
        void generate(AsmCode &asmCode, int level = 0) override;
};

class SymFunc: public SymProcBase {
    public:
        SymFunc(std::string name);
        std::string getString(int depth) override;
};

class SymConst: public Symbol {
    public:
        SymConst(SymbolType type, std::string name);
};

class SymIntegerConst: public SymConst {
    public:
        SymIntegerConst(std::string name, int value);
        std::string getString(int depth);
        int getValue();
        void generateDecl(AsmCode &asmCode) override;
    private:
        int value;
};

class SymFloatConst: public SymConst {
    public:
        SymFloatConst(std::string name, double value);
        std::string getString(int depth);
        double getValue();
        void generateDecl(AsmCode &asmCode) override;
    private:
        double value;
};

#include <iostream>
#include <iomanip>
#include <sstream>
#include "symbols.h"

std::string Symbol::getName() {
    return name;
}

SymbolType Symbol::getType() {
    return type;
}

bool Symbol::isType() {
    return false;
}

std::string Symbol::getString(int depth) {
    std::stringstream sstream;
    sstream << std::string(spacesCount * depth, ' ') << std::left << std::setw(columnWidth1)
            << std::to_string(getSize()) + " " + name;
    return sstream.str();
}

Symbol::Symbol(SymbolType type, std::string name, int size): type(type), name(name), size(size) {}

int Symbol::getSize() {
    return size;
}

void Symbol::generateDecl(AsmCode &asmCode) {
}

void Symbol::generateLValue(AsmCode &asmCode) {
}

void Symbol::setOffset(int offset) {
    this->offset = offset;
}

int Symbol::getOffset() {
    return offset;
}

void Symbol::generateValue(AsmCode &asmCode) {

}

void Symbol::generate(AsmCode &asmCode, int level) {

}

SymbolType Symbol::getVarType() {
    return SymbolType::None;
}

SymVar::SymVar(SymbolType type, std::string name, SymbolPtr varType): Symbol(type, name), varType(varType) {}

std::string SymVar::getTypeName() {
    return varType->getName();
}

SymbolType SymVar::getVarType() {
//    return varType->getType();
    SymbolPtr typeSymbol = getTypeSymbol();
    SymbolType type = typeSymbol->getType();
    if (type == SymbolType::TypeAlias) {
        type = std::dynamic_pointer_cast<SymTypeAlias>(typeSymbol)->getRefSymbol()->getType();
    }
    return type;
}

SymbolPtr SymVar::getTypeSymbol() {
    return varType;
}

int SymVar::getSize() {
    return varType->getSize();
}

void SymVar::generateMemoryCopy(AsmCode& asmCode, AsmCmdPtr cmdMemory, AsmOpType opType) {
    std::string labelBegin = asmCode.genLabelName();
    std::string labelEnd = asmCode.genLabelName();
//    asmCode.addCmd(LEA, RAX, asmCode.getAdressOperand(RBP, -getOffset() - 8));
    asmCode.addCmd(cmdMemory);
    asmCode.addCmd(MOV, RBX, getSize());
    asmCode.addCmd(XOR, RCX, RCX);
    asmCode.addLabel(labelBegin);
    asmCode.addCmd(CMP, RCX, RBX);
    asmCode.addCmd(JGE, labelEnd);
    asmCode.addCmd(MOV, RDX, asmCode.getAdressOperand(RAX));
    asmCode.addCmd(PUSH, RDX);
    asmCode.addCmd(opType, RAX, 8);
    asmCode.addCmd(ADD, RCX, 8);
    asmCode.addCmd(JMP, labelBegin);
    asmCode.addLabel(labelEnd);
}


SymVarConst::SymVarConst(std::string name, SymbolPtr varType): SymVar(SymbolType::VarConst, name, varType) {}

SymVarLocal::SymVarLocal(std::string name, SymbolPtr varType): SymVar(SymbolType::VarLocal, name, varType) {}

void SymVarLocal::generateLValue(AsmCode &asmCode) {
    asmCode.addCmd(LEA, RAX, asmCode.getAdressOperand(RBP, -getOffset() - 8));
    asmCode.addCmd(PUSH, RAX);
}

void SymVarLocal::generateValue(AsmCode &asmCode) {
    if (getSize() == 8) {
        asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RBP, -getOffset() - 8));
        asmCode.addCmd(PUSH, RAX);
    } else {
        generateMemoryCopy(asmCode, AsmCmdPtr(new AsmCmd2(LEA, AsmOperandPtr(new AsmReg(RAX)), asmCode.getAdressOperand(RBP, -getOffset() - 8))), SUB);
    }
}

SymVarGlobal::SymVarGlobal(std::string name, SymbolPtr varType): SymVar(SymbolType::VarGlobal, name, varType) {}

std::string SymVarGlobal::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "var "
            << std::setw(columnWidth3) << getTypeName() << std::endl;
    return sstream.str();
}

void SymVarGlobal::generateDecl(AsmCode &asmCode) {
    std::string varName = asmCode.getVarName(name);
    SymbolType type = varType->getType();
    if (type == SymbolType::TypeAlias) {
        type = std::dynamic_pointer_cast<SymTypeAlias>(varType)->getRefSymbol()->getType(); 
    }
    switch (type) {
        case SymbolType::TypeInteger:
            asmCode.addData(varName, 0);
            break;
        case SymbolType::TypeFloat:
            asmCode.addData(varName, 0.0);
            break;
        case SymbolType::TypeArray:
        case SymbolType::TypeRecord:
            asmCode.addArrayData(varName, getSize());
            break;
    } 
}

void SymVarGlobal::generateLValue(AsmCode &asmCode) {
    asmCode.addCmd(PUSH, asmCode.getVarName(name));
}

void SymVarGlobal::generateValue(AsmCode &asmCode) {
    if (getSize() == 8) {
        asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(asmCode.getVarName(name)));
        asmCode.addCmd(PUSH, RAX);
    } else {
        generateMemoryCopy(asmCode, AsmCmdPtr(new AsmCmd2(MOV, AsmOperandPtr(new AsmReg(RAX)),
                                     AsmOperandPtr(new AsmStringImmediate(asmCode.getVarName(name))))), ADD);
    }
}

SymType::SymType(SymbolType type, std::string name, int size) : Symbol(type, name, size) {}

bool SymType::isType() {
    return true;
}

std::string SymType::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "type " << std::endl;
    return sstream.str();
}

int SymType::getSize() {
    return size;
}

SymTypeFloat::SymTypeFloat(): SymType(SymbolType::TypeFloat, "float", 8) {}

SymTypeInteger::SymTypeInteger(): SymType(SymbolType::TypeInteger, "integer", 8) {}

SymTypeChar::SymTypeChar(): SymType(SymbolType::TypeChar, "char", 1) {}

SymTypePointer::SymTypePointer(SymbolPtr refType): SymType(SymbolType::TypePointer, "pointer", 8), refType(refType) {}

std::string SymTypePointer::getName() {
    return Symbol::getName() + " " + refType->getName();
}

SymTypeRecord::SymTypeRecord(SymTablePtr symTable): SymType(SymbolType::TypeRecord, "record"), symTable(symTable) {}

std::string SymTypeRecord::getString(int depth) {
    std::stringstream sstream;
    sstream << symTable->getString(depth + 1);
    return sstream.str();
}

SymTablePtr SymTypeRecord::getTable() {
    return symTable;
}

int SymTypeRecord::getSize() {
    if (size == 0) {
        for (auto symbol: symTable->getSymbols()) {
            size += symbol->getSize(); 
        } 
    }
    return size;
}

SymConst::SymConst(SymbolType type, std::string name): Symbol(type, name, 8) {}

SymIntegerConst::SymIntegerConst(std::string name, int value): SymConst(SymbolType::ConstInteger, name), value(value) {}

int SymIntegerConst::getValue() {
    return value;
}

std::string SymIntegerConst::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "const int " << std::setw(columnWidth3) << value << std::endl;
    return sstream.str();
}

void SymIntegerConst::generateDecl(AsmCode &asmCode) {
    asmCode.addData(asmCode.getVarName(name), value);
}

void SymFloatConst::generateDecl(AsmCode &asmCode) {
    asmCode.addData(asmCode.getVarName(name), value);
}


SymFloatConst::SymFloatConst(std::string name, double value): SymConst(SymbolType::ConstFloat, name), value(value) {}

double SymFloatConst::getValue() {
    return value;
}

std::string SymFloatConst::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "const float " << std::setw(columnWidth3) << value << std::endl;
    return sstream.str();
}

SymTypeAlias::SymTypeAlias(SymbolPtr refType, std::string name): SymType(SymbolType::TypeAlias, name), refType(refType) {}

SymbolPtr SymTypeAlias::getRefSymbol() {
    return refType;
}

std::string SymTypeAlias::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "type alias "
            << std::setw(columnWidth3) << refType->getName() << std::endl;
    if (refType->getType() == SymbolType::TypeRecord) {
        sstream << refType->getString(depth);
    }
    return sstream.str();
}

int SymTypeAlias::getSize() {
    return refType->getSize();
}

SymbolType SymTypeAlias::getRefType() {
    return refType->getType();
}

SymTypeSubrange::SymTypeSubrange(int left, int right):
        SymType(SymbolType::TypeSubrange, "subrange " + std::to_string(left) + ".." + std::to_string(right)),
        left(left), right(right) {}

int SymTypeSubrange::getLeft() {
    return left;
}

int SymTypeSubrange::getRight() {
    return right;
}

SymParam::SymParam(std::string name, SymbolPtr varType, SymbolPtr method, int offset):
        SymParamBase(SymbolType::Param, name, varType, method, offset) {}

std::string SymParam::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "param "
            << std::setw(columnWidth3) << getTypeName() << std::endl;
    return sstream.str();
}

void SymParam::generateLValue(AsmCode &asmCode) {
    asmCode.addCmd(LEA, RAX, asmCode.getAdressOperand(RBP, offset + 8));
    asmCode.addCmd(PUSH, RAX);
}

void SymParam::generateValue(AsmCode &asmCode) {
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RBP, offset + 8));
    asmCode.addCmd(PUSH, RAX);
}

SymVarParam::SymVarParam(std::string name, SymbolPtr varType, SymbolPtr method, int offset):
        SymParamBase(SymbolType::VarParam, name, varType, method, offset) {}

std::string SymVarParam::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "var param "
            << std::setw(columnWidth3) << getTypeName() << std::endl;
    return sstream.str();
}

void SymVarParam::generateLValue(AsmCode &asmCode) {
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RBP, offset + 8));
    asmCode.addCmd(PUSH, RAX);
}

void SymVarParam::generateValue(AsmCode &asmCode) {
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RBP, offset + 8));
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(RAX));
    asmCode.addCmd(PUSH, RAX);
}

int SymVarParam::getSize() {
    return 8;
}

SymFuncResult::SymFuncResult(std::string name, SymbolPtr varType, SymbolPtr method):
        SymParamBase(SymbolType::FuncResult, name, varType, method, 0) {}

std::string SymFuncResult::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "func result "
            << std::setw(columnWidth3) << getTypeName() << std::endl;
    return sstream.str();
}

void SymFuncResult::generateLValue(AsmCode &asmCode) {
    asmCode.addCmd(LEA, RAX, asmCode.getAdressOperand(
            RBP, std::dynamic_pointer_cast<SymProcBase>(method)->getArgs()->getSize() + 8));
    asmCode.addCmd(PUSH, RAX);
}

void SymFuncResult::generateValue(AsmCode &asmCode) {
    asmCode.addCmd(MOV, RAX, asmCode.getAdressOperand(
            RBP, std::dynamic_pointer_cast<SymProcBase>(method)->getArgs()->getSize() + 8));
    asmCode.addCmd(PUSH, RAX);
}

SymParamBase::SymParamBase(SymbolType type, std::string name, SymbolPtr varType, SymbolPtr method, int offset):
        SymVar(type, name, varType), method(method) {}

SymProcBase::SymProcBase(SymbolType type, std::string name):
        Symbol(type, name) {}

SymProc::SymProc(std::string name): SymProcBase(SymbolType::Proc, name) {}

std::string SymProc::getString(int depth) {
    std::stringstream sstream;
    sstream << Symbol::getString(depth) << std::setw(columnWidth2) << "proc" << std::endl;
    sstream << SymProcBase::getString(depth);
    return sstream.str();
}

void SymProc::generate(AsmCode &asmCode, int level) {
    for (auto symbol: locals->getSymbols()) {
        symbol->generate(asmCode, level);
    }
}

SymFunc::SymFunc(std::string name): SymProcBase(SymbolType::Func, name) {}

std::string SymFunc::getString(int depth) {
    std::stringstream sstream;
    sstream << std::left << Symbol::getString(depth) << std::right << std::setw(columnWidth2) << "func" << std::endl;
    sstream << SymProcBase::getString(depth);
    return sstream.str();
}

void SymProcBase::setArgs(SymTablePtr args) {
    this->args = args;
}

void SymProcBase::setLocals(SymTablePtr locals) {
    this->locals = locals;
}

SymTablePtr SymProcBase::getArgs() {
    return args;
}

std::string SymProcBase::getString(int depth) {
    std::stringstream sstream;
    sstream << std::string(spacesCount * depth, ' ') << std::left << std::setw(columnWidth1) << "args:" << std::endl << args->getString(depth + 1);
    sstream << std::string(spacesCount * depth, ' ') << std::setw(columnWidth1) << "locals:" << std::endl << locals->getString(depth + 1);
    return sstream.str();
}

SymTablePtr SymProcBase::getLocals() {
    return locals;
}

void SymProcBase::setLevel(int level) {
    this->level = level;
}

int SymProcBase::getLevel() {
    return level;
}

SymTypeArray::SymTypeArray(SymbolPtr elemType, int left, int right): SymType(SymbolType::TypeArray, "array"),
                                                                      elemType(elemType), left(left), right(right) {}

void SymTypeArray::setElemType(SymbolPtr elemType) {
    this->elemType = elemType;
}

std::string SymTypeArray::getName() {
    return Symbol::getName() + "[" + std::to_string(left) + ".." + std::to_string(right) + "] of " + elemType->getName();
}

SymbolType SymTypeArray::getElemType() {
    if (elemType->getType() == SymbolType::TypeArray) {
        return std::dynamic_pointer_cast<SymTypeArray>(elemType)->getElemType();
    }
    return elemType->getType();
}

SymbolPtr SymTypeArray::getElemSybmol() {
    return elemType; 
}

int SymTypeArray::getSize() {
    if (!size) {
        size = elemType->getSize() * (right - left + 1);
    }
    return size;
}

int SymTypeArray::getLowRange() {
    return left;
}

SymTypeOpenArray::SymTypeOpenArray(SymbolPtr elemType): SymType(SymbolType::TypeOpenArray, "open array"),
                                                         elemType(elemType) {}


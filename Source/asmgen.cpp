#include <sstream>
#include <string>
#include "asmgen.h"

AsmCmd::AsmCmd(AsmOpType opType, AsmOperandPtr operand1, AsmOperandPtr operand2): opType(opType), operand1(operand1),
                                                                                  operand2(operand2) {}

AsmOpType AsmCmd::getOpType() {
    return opType;
}

AsmCmdType AsmCmd::getCmdType() {
    return AsmCmdType::Cmd;
}

AsmOperandPtr AsmCmd::getOperand1() {
    return operand1;
}

AsmOperandPtr AsmCmd::getOperand2() {
    return operand2;
}

std::string AsmCmd::getString() {
    return std::string();
}

AsmCmd0::AsmCmd0(AsmOpType opType): AsmCmd(opType) {}

std::string AsmCmd0::getString() {
    return "\t" + asmOpNames[opType];
}

AsmCmdType AsmCmd0::getCmdType() {
    return AsmCmdType::Cmd0;
}

AsmCmd1::AsmCmd1(AsmOpType opType, AsmOperandPtr operand): AsmCmd(opType, operand) {}

std::string AsmCmd1::getString() {
    return "\t" + asmOpNames[opType] + " " + operand1->getString();
}

AsmCmdType AsmCmd1::getCmdType() {
    return AsmCmdType::Cmd1;
}

AsmCmd2::AsmCmd2(AsmOpType opType, AsmOperandPtr operand1, AsmOperandPtr operand2) : AsmCmd(opType, operand1,
                                                                                            operand2) {
    if (operand2->getOperandType() == AsmOperandType::Memory && operand1->getOperandType() == AsmOperandType::Reg) {
        std::dynamic_pointer_cast<AsmMemory>(operand2)->clearSize(); 
    }
}

std::string AsmCmd2::getString() {
    return "\t" + asmOpNames[opType] + " " + operand1->getString() + ", " + operand2->getString();
}

AsmCmdType AsmCmd2::getCmdType() {
    return AsmCmdType::Cmd2;
}

AsmReg::AsmReg(AsmRegType reg): reg(reg) {}

std::string AsmReg::getString() {
    return asmRegNames[reg];
}

AsmOperandType AsmReg::getOperandType() {
    return AsmOperandType::Reg;
}

AsmRegType AsmReg::getRegType() {
    return reg;
}

void AsmCode::addCmd(AsmOpType opType) {
    addCmd(AsmCmdPtr(new AsmCmd0(opType)));
}

void AsmCode::addCmd(AsmOpType opType, AsmOperandPtr operand) {
    addCmd(AsmCmdPtr(new AsmCmd1(opType, operand)));
}


void AsmCode::addCmd(AsmOpType opType, AsmRegType reg) {
    addCmd(AsmCmdPtr(new AsmCmd1(opType, AsmOperandPtr(new AsmReg(reg)))));
}

void AsmCode::addCmd(AsmOpType opType, AsmRegType destReg, AsmRegType sourceReg) {
    addCmd(AsmCmdPtr(new AsmCmd2(opType, AsmOperandPtr(new AsmReg(destReg)),
                                             AsmOperandPtr(new AsmReg(sourceReg)))));
}

void AsmCode::addCmd(AsmOpType opType, AsmRegType reg, std::string data) {
    addCmd(AsmCmdPtr(new AsmCmd2(opType, AsmOperandPtr(new AsmReg(reg)),
                                             AsmOperandPtr(new AsmStringImmediate(data)))));
}

void AsmCode::addCmd(AsmOpType opType, AsmRegType reg, int value) {
    addCmd(AsmCmdPtr(new AsmCmd2(opType, AsmOperandPtr(new AsmReg(reg)),
                                             AsmOperandPtr(new AsmIntImmediate(value)))));
}


void AsmCode::addCmd(AsmOpType opType, AsmOperandPtr operand, AsmRegType reg) {
    addCmd(AsmCmdPtr(new AsmCmd2(opType, operand, AsmOperandPtr(new AsmReg(reg)))));
}

void AsmCode::addCmd(AsmOpType opType, AsmRegType reg, AsmOperandPtr operand) {
    addCmd(AsmCmdPtr(new AsmCmd2(opType, AsmOperandPtr(new AsmReg(reg)), operand)));
}

std::string AsmCode::getString() {
    std::stringstream sstream;
    sstream << "global  main" << std::endl;
    sstream << "extern  printf" << std::endl;
    sstream << "section .text" << std::endl;
    for (auto command: commands) {
        sstream << command->getString() << std::endl; 
    }
    sstream << "section .data" << std::endl;
    for (auto asmData: data) {
        sstream << asmData->getString() << std::endl;
    }
    return sstream.str();
}

void AsmCode::addCmd(AsmOpType opType, int value) {
    addCmd(AsmCmdPtr(new AsmCmd1(opType, AsmOperandPtr(new AsmIntImmediate(value)))));
}

void AsmCode::addCmd(AsmOpType opType, std::string value) {
    addCmd(AsmCmdPtr(new AsmCmd1(opType, AsmOperandPtr(new AsmStringImmediate(value)))));
}

void AsmCode::addData(std::string name, std::string value) {
    data.push_back(AsmDataPtr(new AsmStringData(name, value)));
}

AsmCode::AsmCode(): namesCount(0), pushCount(0), labelsCount(0) {
    addData("formatInt", "\"%ld\"");
    addData("formatFloat", "\"%f\"");
    addData("formatNewLine", "10");
}

void AsmCode::addWriteInt() {
    addCmd(POP, RAX);
    addCmd(MOV, RSI, RAX);
    addCmd(XOR, RAX, RAX);
    addWrite("formatInt");
}

void AsmCode::addWriteFloat() {
    addCmd(POP, RAX);
    addCmd(MOVQ, XMM0, RAX);
    addCmd(MOV, RAX, 1);
    addWrite("formatFloat");
}

void AsmCode::addWriteString(std::string value) {
    std::string name = genVarName();
    addData(name, "\"" + value + "\"");
    addCmd(XOR, RAX, RAX);
    addWrite(name);
}


void AsmCode::addWrite(std::string format) {
    addCmd(MOV, RDI, format);
    bool addSub = false;
    if (pushCount % 2 == 0) {
        addCmd(SUB, RSP, 8);
        addSub = true;
    }
    addCmd(CALL, "printf");
    if (addSub) {
        addCmd(ADD, RSP, 8);
    }
}

void AsmCode::addWriteNewLine() {
    addCmd(XOR, RAX, RAX);
    addWrite("formatNewLine");
}

std::string AsmCode::getVarName(std::string name) {
    return "v_" + name;
}

void AsmCode::addData(std::string name, int value) {
    data.push_back(AsmDataPtr(new AsmIntData(name, value)));
}

void AsmCode::addArrayData(std::string name, int size) {
    data.push_back(AsmDataPtr(new AsmArrayData(name, size)));
}

void AsmCode::addData(std::string name, double value) {
    data.push_back(AsmDataPtr(new AsmFloatData(name, value)));
}

AsmOperandPtr AsmCode::getAdressOperand(std::string name, int offset) {
    return AsmOperandPtr(new AsmMemory(name, offset));
}

AsmOperandPtr AsmCode::getAdressOperand(AsmRegType reg, int offset) {
    return AsmOperandPtr(new AsmMemory(reg, offset));
}

std::string AsmCode::genVarName() {
    return "v_" + std::to_string(namesCount++);
}

void AsmCode::addCmd(AsmCmdPtr cmd) {
    if (cmd->getOpType() == AsmOpType::PUSH) {
        ++pushCount;
    } else if (cmd->getOpType() == AsmOpType::POP) {
        --pushCount;
    } else if (cmd->getCmdType() == AsmCmdType::Cmd2 && cmd->getOpType() == AsmOpType::SUB
            && cmd->getOperand1()->getOperandType() == AsmOperandType::Reg
            && std::dynamic_pointer_cast<AsmReg>(cmd->getOperand1())->getRegType() == AsmRegType::RSP
            && cmd->getOperand2()->getOperandType() == AsmOperandType::IntImmediate) {
        pushCount += std::dynamic_pointer_cast<AsmIntImmediate>(cmd->getOperand2())->getValue() / 8;
    } else if (cmd->getCmdType() == AsmCmdType::Cmd2 && cmd->getOpType() == AsmOpType::ADD
            && cmd->getOperand1()->getOperandType() == AsmOperandType::Reg
            && std::dynamic_pointer_cast<AsmReg>(cmd->getOperand1())->getRegType() == AsmRegType::RSP
            && cmd->getOperand2()->getOperandType() == AsmOperandType::IntImmediate) {
        pushCount -= std::dynamic_pointer_cast<AsmIntImmediate>(cmd->getOperand2())->getValue() / 8;
    }
    commands.push_back(cmd);
}

std::string AsmCode::genLabelName() {
    return "L" + std::to_string(labelsCount++);
}

void AsmCode::addLabel(std::string name) {
    addCmd(AsmCmdPtr(new AsmLabel(name)));
}

void AsmCode::addLabels(std::string nameContinue, std::string nameBreak) {
    labelsContinue.push(nameContinue);
    labelsBreak.push(nameBreak);
}

void AsmCode::deleteLabels() {
    labelsContinue.pop();
    labelsBreak.pop();
}

std::string AsmCode::getLabelContinue() {
    if (labelsContinue.empty()) {
        return "";
    }
    return labelsContinue.top();
}

std::string AsmCode::getLabelBreak() {
    if (labelsBreak.empty()) {
        return "";
    }
    return labelsBreak.top();
}

AsmIntImmediate::AsmIntImmediate(int value): value(value) {}

std::string AsmIntImmediate::getString() {
    return std::to_string(value);
}

AsmOperandType AsmIntImmediate::getOperandType() {
    return AsmOperandType::IntImmediate;
}

int AsmIntImmediate::getValue() {
    return value;
}

AsmData::AsmData(std::string name): name(name) {}

AsmArrayData::AsmArrayData(std::string name, int size): AsmData(name), size(size) {}

std::string AsmArrayData::getString() {
    return "\t" + name + ": times " + std::to_string(size) + " db 0";
}

AsmFloatData::AsmFloatData(std::string name, double value): AsmData(name), value(value) {}

std::string AsmFloatData::getString() {
    return "\t" + name + ": dq " + std::to_string(value);
}

AsmStringData::AsmStringData(std::string name, std::string value): AsmData(name), value(value) {}

std::string AsmStringData::getString() {
    return "\t" + name + ": db " + value + ", 0";
}

AsmStringImmediate::AsmStringImmediate(std::string value): value(value) {}

std::string AsmStringImmediate::getString() {
    return value;
}

AsmOperandType AsmStringImmediate::getOperandType() {
    return AsmOperandType::StringImmediate;
}

AsmIntData::AsmIntData(std::string name, int value): AsmData(name), value(value) {}

std::string AsmIntData::getString() {
    return "\t" + name + ": dq " + std::to_string(value);
}

AsmMemory::AsmMemory(std::string name, int offset): offset(offset), operand(new AsmStringImmediate(name)) {}

AsmMemory::AsmMemory(AsmRegType reg, int offset): offset(offset), operand(new AsmReg(reg)) {}

std::string AsmMemory::getString() {
    std::string op = offset > 0 ? " + " : " - "; 
    std::string sizeStr = !size.empty() ? size + " " : "";
    return sizeStr + "[" + operand->getString() + (!offset ? "" : (op + std::to_string(abs(offset)))) + "]"; 
}

AsmOperandType AsmMemory::getOperandType() {
    return AsmOperandType::Memory;
}

AsmOperandPtr AsmMemory::getOperand() {
    return operand;
}

AsmMemory::AsmMemory(const AsmMemory &adress): operand(adress.operand), offset(adress.offset), size("qword") {}

AsmMemory::AsmMemory(AsmOperandPtr memoryOperand) {
    AsmMemoryPtr memory = std::dynamic_pointer_cast<AsmMemory>(memoryOperand);
    operand = memory->operand;
    offset = memory->offset;
    size = "qword";
}

void AsmMemory::clearSize() {
    size.clear();
}

void AsmMemory::addOffset(int value) {
    offset += value; 
}

int AsmMemory::getOffset() {
    return offset;
}

AsmLabel::AsmLabel(std::string name): AsmCmd(LABEL), name(name) {}

std::string AsmLabel::getString() {
    return name + ":";
}

AsmCmdType AsmLabel::getCmdType() {
    return AsmCmdType::Label;
}

AsmOperandType AsmOperand::getOperandType() {
    return AsmOperandType::Operand;
}

bool AsmOperand::isImmediate() {
    return false;
}

bool AsmImmediate::isImmediate() {
    return true;
}


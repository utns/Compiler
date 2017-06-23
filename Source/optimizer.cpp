#include <iostream>
#include <set>
#include "optimizer.h"

Optimizer::Optimizer(AsmCode& asmCode): asmCode(asmCode), commands(asmCode.commands) {
    //--------------------*1*---------------------//
    //sub/add Reg, 0
    //->
    optimizerFunctions.push_back([&](int i) -> bool {
        if ((checkOpType(i, ADD) || checkOpType(i, SUB))
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && getIntImmediate(getOperand2(i)) == 0) {
            deleteCommands(i);
            return true;
        }
        return false;
    });

    //mov(q) Reg, Reg
    //->
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpTypeIsMovOrMovq(i) && checkRegType(getOperand1(i), getOperand2(i))) {
            deleteCommands(i);
            return true;
        }
        return false;
    });


    //mov Reg, 0
    //->xor Reg, Reg
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOperand1Type(i, AsmOperandType::Reg)
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && getIntImmediate(getOperand2(i)) == 0) {
            commands[i] = AsmCmdPtr(new AsmCmd2(XOR, getOperand1(i), getOperand1(i)));
            return true;
        }
        return false;
    });

    //lea Reg, [Adress]
    //->mov Reg, Adress
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, LEA) && (getMemoryOffset(getOperand2(i)) == 0)) {
            AsmOperandPtr adress = std::dynamic_pointer_cast<AsmMemory>(getOperand2(i))->getOperand();
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i), adress));
            return true;
        }
        return false;
    });

    //--------------------*2*---------------------//
    //push Reg
    //pop Reg 
    //->
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, PUSH) && checkOpType(i + 1, POP)
                && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            deleteCommands(i, 2);
            return true;
        }
        return false;
    });

    //push Reg1/Memory
    //pop Reg2 
    //->mov Reg2, Reg1/Memory 
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, PUSH) && checkOpType(i + 1, POP)
                && !(checkRegType(getOperand1(i), getOperand1(i + 1)))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i + 1), getOperand1(i)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg1, Reg2/Memory/(Imeediate)
    //cmd(mov) operand(!memory), Reg1
    //->cmd operand, Reg2/Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV)
                && (!(getOperand2(i)->isImmediate()) || 
                    (checkOpType(i + 1, MOV) && checkOperand1Type(i + 1, AsmOperandType::Reg))) 
                && (!checkOperand2Type(i, AsmOperandType::Memory)
                    || checkOperand1Type(i + 1, AsmOperandType::Reg))
                && checkCmdType(i + 1, AsmCmdType::Cmd2)
                && checkRegType(getOperand1(i), getOperand2(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(commands[i + 1]->getOpType(), getOperand1(i + 1),
                                                getOperand2(i)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg, Int1
    //add/sub Reg, Int2
    //->add/sub Reg, Int1 +/- Int2 
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV)
                && checkOperand1Type(i, AsmOperandType::Reg)
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && (checkOpType(i + 1, ADD) || checkOpType(i + 1, SUB))
                && checkOperand2Type(i + 1, AsmOperandType::IntImmediate)) {
            int value1 = getIntImmediate(getOperand2(i));
            int value2 = getIntImmediate(getOperand2(i + 1));
            int value = checkOpType(i + 1, ADD) ? value1 + value2 : value1 -value2;
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i + 1),
                                                AsmOperandPtr(new AsmIntImmediate(value))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov(q) Reg1, Reg2
    //mov(q) Reg2, Reg1
    //->
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpTypeIsMovOrMovq(i) && checkOpTypeIsMovOrMovq(i + 1)
                && checkRegType(getOperand1(i), getOperand2(i + 1))
                && checkRegType(getOperand2(i), getOperand1(i + 1))) {
            deleteCommands(i, 2);
            return true;
        }
        return false;
    });

    //mov(q) Reg1, Memory
    //cmd Reg2, Reg1
    //->cmd Reg2, Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpTypeIsMovOrMovq(i) && checkOperand2Type(i, AsmOperandType::Memory)
                && checkCmdType(i + 1, AsmCmdType::Cmd2)
                && checkOperand1Type(i + 1, AsmOperandType::Reg)
                && checkRegType(getOperand1(i), getOperand2(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(commands[i + 1]->getOpType(), getOperand1(i + 1),
                                                getOperand2(i)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //movq Reg1, Xmm1
    //mov Reg2, Reg1
    //->movq Reg2, Xmm1
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOVQ) && checkOpTypeIsMovOrMovq(i + 1)
                && checkRegType(getOperand1(i), getOperand2(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(commands[i]->getOpType(), getOperand1(i + 1),
                                                getOperand2(i)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //xor Reg1, Reg1
    //sub/add Reg2, Reg1
    //->xor
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, XOR) && (checkOpType(i + 1, ADD) || checkOpType(i + 1, SUB))
                && checkRegType(getOperand1(i), getOperand1(i))
                && checkRegType(getOperand1(i), getOperand2(i + 1))) {
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg1, Adress
    //mov [Reg1], Reg2
    //->mov [Adress], Reg2
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOperand2Type(i, AsmOperandType::StringImmediate)
                && checkOpType(i + 1, MOV) && checkOperand2Type(i + 1, AsmOperandType::Reg)
                && checkAdressReg(getOperand1(i + 1), getOperand1(i))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV,
                                                AsmOperandPtr(new AsmMemory(getOperand2(i)->getString())),
                                                getOperand2(i + 1)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //cmd Reg1, Operand
    //mov Reg1, Operand(![Reg1])
    //->mov Reg1, Operand
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkCmdType(i, AsmCmdType::Cmd2) && checkOpType(i + 1, MOV)
                && (!checkOperand2Type(i + 1, AsmOperandType::Memory)
                    || !checkAdressReg(getOperand2(i + 1), getOperand1(i)))
                && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            deleteCommands(i);
            return true;
        }
        return false;
    });

    //mov Reg1, Memory
    //imul/idiv Reg1
    //->imul/idiv qword Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV)
                && (checkOpType(i + 1, IDIV) || checkOpType(i + 1, IMUL))
                && checkOperand2Type(i, AsmOperandType::Memory)
                && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd1(commands[i + 1]->getOpType(),
                                                AsmOperandPtr(new AsmMemory(getOperand2(i)))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg1, Memory
    //cmd Reg, Reg1
    //->cmd Reg, qword Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkCmdType(i + 1, AsmCmdType::Cmd2)
                && checkOperand1Type(i + 1, AsmOperandType::Reg)
                && checkOperand2Type(i, AsmOperandType::Memory)
                && checkRegType(getOperand1(i), getOperand2(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(commands[i + 1]->getOpType(),
                                                getOperand1(i + 1),
                                                AsmOperandPtr(new AsmMemory(getOperand2(i)))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg1, Adress
    //mov Reg1, [Reg1]
    //->mov Reg, [Reg1]
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOperand2Type(i, AsmOperandType::StringImmediate)
                && checkOpType(i + 1, MOV) && checkOperand1Type(i + 1, AsmOperandType::Reg)
                && checkRegType(getOperand1(i), getOperand1(i + 1))
                && checkAdressReg(getOperand2(i + 1), getOperand1(i))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV,
                                                getOperand1(i + 1),
                                                AsmOperandPtr(new AsmMemory(getOperand2(i)->getString()))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //jmp L1
    //jmp L2
    //->jmp L1
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, JMP) && checkOpType(i + 1, JMP)) {
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg, Memory
    //push Reg
    //->push qword Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOperand2Type(i, AsmOperandType::Memory)
                && checkOpType(i + 1, PUSH) && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            commands[i] = AsmCmdPtr(new AsmCmd1(PUSH, AsmOperandPtr(new AsmMemory(getOperand2(i)))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //lea Reg1, [Reg2 + Int1]
    //add/sub Reg1, Int2
    //lea Reg1, [Reg2 + Int1 +/- Int2]
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, LEA) && (checkOpType(i + 1, ADD) || checkOpType(i + 1, SUB))
                && checkOperand2Type(i + 1, AsmOperandType::IntImmediate)
                && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            int value = getIntImmediate(getOperand2(i + 1));
            if (checkOpType(i + 1, SUB)) {
                value *= -1;
            }
            std::dynamic_pointer_cast<AsmMemory>(getOperand2(i))->addOffset(value);
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //mov Reg, Adress
    //add/sub Reg, Int
    //->lea Reg, [Adress +/- Int]
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOperand2Type(i, AsmOperandType::StringImmediate)
                && (checkOpType(i + 1, ADD) || checkOpType(i + 1, SUB))
                && checkOperand2Type(i + 1, AsmOperandType::IntImmediate)
                && checkRegType(getOperand1(i), getOperand1(i + 1))) {
            int offset = getIntImmediate(getOperand2(i + 1));
            if (checkOpType(i + 1, SUB)) {
                offset *= -1;
            }
            commands[i] = AsmCmdPtr(new AsmCmd2(LEA, getOperand1(i),
                                                AsmOperandPtr(new AsmMemory(getOperand2(i)->getString(),
                                                                            offset))));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //lea Reg1, Memory
    //mov Reg2, [Reg1]
    //->mov Reg2, Memory
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, LEA) && checkOpType(i + 1, MOV)
                && checkAdressReg(getOperand2(i + 1), getOperand1(i))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i + 1), getOperand2(i)));
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });

    //--------------------*3*---------------------//
    //push Reg1
    //cmd Reg2, Reg3/Memory
    //pop Reg4
    //->mov Reg4, Reg2/3
    //->cmd Reg2, Reg3/Memory
    // or
    //->cmd Reg2, Reg3/Memory
    //->mov Reg2/3, Reg1 
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, PUSH) && checkCmdType(i + 1, AsmCmdType::Cmd2)
                && checkOpType(i + 2, POP)) {
            if (checkOperand1Type(i, AsmOperandType::Reg)
                    && checkFreeReg(i + 1, getOperand1(i))) {
                if (checkRegType(getOperand1(i), getOperand1(i + 2))) {
                    deleteCommands(i);
                    deleteCommands(i + 1);
                } else {
                    commands[i + 2] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i + 2),
                                                            getOperand1(i)));
                    deleteCommands(i);
                }
                return true;
            } else if (checkOperand1Type(i + 2, AsmOperandType::Reg)
                       && checkFreeReg(i + 1, getOperand1(i + 2))) {
                commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i + 2),
                                                        getOperand1(i)));
                deleteCommands(i + 2);
                return true;
            }
        }
        return false;
    });

    //pop Reg1
    //add/sub Reg1, (operand != Reg2)
    //mov Reg2, Reg1 
    //->pop Reg2
    //->add/sub Reg2, operand 
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, POP)
                && (checkOpType(i + 1, ADD) || checkOpType(i + 1, SUB))
                && checkOpType(i + 2, MOV)
                && checkRegType(getOperand1(i), getOperand1(i + 1))
                && checkRegType(getOperand1(i + 1), getOperand2(i + 2))
                && (!checkOperand2Type(i + 1, AsmOperandType::Reg)
                    || !checkRegType(getOperand2(i + 1), getOperand1(i + 2)))) {
            commands[i] = AsmCmdPtr(new AsmCmd1(POP, getOperand1(i + 2)));
            commands[i + 1] = AsmCmdPtr(new AsmCmd2(commands[i + 1]->getOpType(), getOperand1(i + 2),
                                                    getOperand2(i + 1)));
            deleteCommands(i + 2);
            return true;
        }
        return false;
    });

    //mov(q) Reg1, Reg2
    //cmd Reg3, Reg4
    //mov(q) Reg2, Reg1
    //->cmd Reg3, Reg4
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpTypeIsMovOrMovq(i) && checkOpTypeIsMovOrMovq(i + 2)
                && checkRegType(getOperand1(i), getOperand2(i + 2))
                && checkRegType(getOperand2(i), getOperand1(i + 2))
                && checkFreeReg(i + 1, getOperand1(i))
                && checkFreeReg(i + 1, getOperand2(i))) {
            deleteCommands(i);
            deleteCommands(i + 1);
            return true;
        }
        return false;
    });
    
    //mov rax, int1
    //mov Reg, int2
    //imul Reg
    //->mov rax, int1 * int2
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOpType(i + 1, MOV) && checkOpType(i + 2, IMUL)
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && checkOperand2Type(i + 1, AsmOperandType::IntImmediate)
                && checkRegType(getOperand1(i), AsmRegType::RAX)
                && checkRegType(getOperand1(i + 1), getOperand1(i + 2))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i),
                                                AsmOperandPtr(new AsmIntImmediate(
                                                        getIntImmediate(getOperand2(i))
                                                        * getIntImmediate(getOperand2(i + 1))))));
            deleteCommands(i + 1, 2);
            return true;
        }
        return false;
    });

    //mov Reg1, Int1
    //mov Reg2, Int2
    //add/sub Reg1, Reg2
    //->mov Reg1, Int1 +/- Int2
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV) && checkOpType(i + 1, MOV)
                && (checkOpType(i + 2, ADD) || checkOpType(i + 2, SUB))
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && checkOperand2Type(i + 1, AsmOperandType::IntImmediate)
                && checkRegType(getOperand1(i), getOperand1(i + 2))
                && checkRegType(getOperand1(i + 1), getOperand2(i + 2))) {
            int value1 = getIntImmediate(getOperand2(i));
            int value2 = getIntImmediate(getOperand2(i + 1));
            int value = checkOpType(i + 1, ADD) ? value1 + value2 : value1 - value2;
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i), AsmOperandPtr(new AsmIntImmediate(value))));
            deleteCommands(i + 1, 2);
            return true;
        }
        return false;
    });

    //--------------------*4*---------------------//
    //mov Reg1, Int1
    //add/sub Reg2, Reg1
    //mov Reg3, Int2
    //add/sub Reg2, Reg3
    //->mov Reg1, Int1 +/- Int2
    //->add Reg2, Reg1
    optimizerFunctions.push_back([&](int i) -> bool {
        if (checkOpType(i, MOV)
                && ((checkOpType(i + 1, ADD) && checkOpType(i + 3, ADD))
                    || (checkOpType(i + 1, SUB) && checkOpType(i + 3, SUB)))
                && checkOpType(i + 2, MOV)
                && checkOperand2Type(i, AsmOperandType::IntImmediate)
                && checkOperand2Type(i + 2, AsmOperandType::IntImmediate)
                && checkRegType(getOperand1(i), getOperand2(i + 1))
                && checkRegType(getOperand1(i + 2), getOperand2(i + 3))
                && checkRegType(getOperand1(i + 1), getOperand1(i + 3))) {
            commands[i] = AsmCmdPtr(new AsmCmd2(MOV, getOperand1(i),
                                                AsmOperandPtr(new AsmIntImmediate(
                                                        getIntImmediate(getOperand2(i))
                                                        + getIntImmediate(getOperand2(i + 2))))));
            deleteCommands(i + 2, 2);
            return true;
        }
        return false;
    });
    

    optFuncStat.resize(optimizerFunctions.size(), 0);
}

void Optimizer::optimize() {
    commands.push_back(AsmCmdPtr(new AsmCmd(NONE)));
    commands.push_back(AsmCmdPtr(new AsmCmd(NONE)));
    commands.push_back(AsmCmdPtr(new AsmCmd(NONE)));
    int maxIter = 100;
    bool optimizeSmth = true;
    int optIter = 0;
    for (; optIter < maxIter && optimizeSmth; ++optIter) {
        optimizeSmth = false;
        for (int i = 0; i < (int)commands.size() - 3; ++i) {
            for (int j = 0; j < optimizerFunctions.size(); ++j) {
                bool res = optimizerFunctions[j](i);
                optFuncStat[j] += res;
                optimizeSmth |= res;
            }
        }
    }
    for (int i = 0; i < optFuncStat.size(); ++i) {
        std::cout << optFuncStat[i] << " ";
    }
    std::cout << "Iter " << optIter << std::endl;
    deleteLabels();
    deleteCommands(commands.size() - 3, 3);
}

bool Optimizer::checkCmdType(int i, AsmCmdType cmdType) {
    return commands[i]->getCmdType() == cmdType;
}

bool Optimizer::checkOpType(int i, AsmOpType opType) {
    return commands[i]->getOpType() == opType;
}

bool Optimizer::checkOperand1Type(int i, AsmOperandType operandType) {
    return getOperand1(i)->getOperandType() == operandType;
}

bool Optimizer::checkOperand2Type(int i, AsmOperandType operandType) {
    return getOperand2(i)->getOperandType() == operandType;
}

bool Optimizer::checkRegType(AsmOperandPtr operand1, AsmOperandPtr operand2) {
    return operand1->getOperandType() == AsmOperandType::Reg &&
           operand2->getOperandType() == AsmOperandType::Reg &&
           std::dynamic_pointer_cast<AsmReg>(operand1)->getRegType() 
           == std::dynamic_pointer_cast<AsmReg>(operand2)->getRegType();
}

int Optimizer::getIntImmediate(AsmOperandPtr operand) {
    return std::dynamic_pointer_cast<AsmIntImmediate>(operand)->getValue();
}

void Optimizer::deleteCommands(int startPos, int count) {
    if (count > 0) {
        commands.erase(commands.begin() + startPos, commands.begin() + startPos + count);
    }
}

bool Optimizer::checkFreeReg(int command, AsmOperandPtr regOperand) {
    AsmRegType reg = std::dynamic_pointer_cast<AsmReg>(regOperand)->getRegType();
    if ((checkCmdType(command, AsmCmdType::Cmd1) || checkCmdType(command, AsmCmdType::Cmd2)) 
            && checkOperand1Type(command, AsmOperandType::Reg) 
            && checkRegType(commands[command]->getOperand1(), reg)) {
        return false;
    } else if (checkCmdType(command, AsmCmdType::Cmd2)
               && checkOperand2Type(command, AsmOperandType::Reg) 
               && checkRegType(commands[command]->getOperand2(), reg)) {
        return false;
    }
    return true;
}

bool Optimizer::checkRegType(AsmOperandPtr operand, AsmRegType reg) {
    return std::dynamic_pointer_cast<AsmReg>(operand)->getRegType() == reg;
}

bool Optimizer::checkOpTypeIsMovOrMovq(int i) {
    return checkOpType(i, MOV) || checkOpType(i, MOVQ);
}

bool Optimizer::checkAdressReg(AsmOperandPtr memory, AsmOperandPtr reg) {
    return memory->getOperandType() == AsmOperandType::Memory
           && checkRegType(std::dynamic_pointer_cast<AsmMemory>(memory)->getOperand(), reg);
}

int Optimizer::getMemoryOffset(AsmOperandPtr operand) {
    return std::dynamic_pointer_cast<AsmMemory>(operand)->getOffset();
}

AsmOperandPtr Optimizer::getOperand1(int i) {
    return commands[i]->getOperand1();
}

AsmOperandPtr Optimizer::getOperand2(int i) {
    return commands[i]->getOperand2();
}

void Optimizer::deleteLabels() {
    std::map<std::string, std::string> deletedLabels;
    std::set<std::string> usedLabels;
    for (int i = 0; i < commands.size() - 1; ++i) {
        if (checkCmdType(i, AsmCmdType::Label)) {
            std::string startLabel = commands[i]->getString();
            startLabel.pop_back();
            usedLabels.insert(startLabel);
            int j = i + 1;
            while (checkCmdType(j, AsmCmdType::Label)) {
                std::string label = commands[j]->getString();
                label.pop_back();
                deletedLabels[label] = startLabel;
                ++j;
            }
            deleteCommands(i + 1, j - i - 1);
        }
    }
    for (int i = 0; i < commands.size(); ) {
        if (isJumpCmd(i) && (usedLabels.find(getJumpLabel(i)) == usedLabels.end())) {
            if (deletedLabels.find(getJumpLabel(i)) != deletedLabels.end()) {
                commands[i] = AsmCmdPtr(new AsmCmd1(commands[i]->getOpType(), AsmOperandPtr(new AsmStringImmediate(deletedLabels[getJumpLabel(i)]))));
                ++i;
            } else {
                deleteCommands(i);
            }
        } else {
            ++i;
        }
    }
//    std::cout << deletedLabels.size() << std::endl;
    return;
}

bool Optimizer::isJumpCmd(int i) {
    return checkOpType(i, JMP) || checkOpType(i, JE) || checkOpType(i, JNE)
        || checkOpType(i, JL) || checkOpType(i, JLE) || checkOpType(i, JGE)
        || checkOpType(i, JG) || checkOpType(i, JB) || checkOpType(i, JBE)
        || checkOpType(i, JAE) || checkOpType(i, JA) || checkOpType(i, JZ);
}

std::string Optimizer::getJumpLabel(int i) {
    return commands[i]->getOperand1()->getString();
}






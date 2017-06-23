#pragma once

#include <functional>
#include "asmgen.h"

class Optimizer {
    public:
        Optimizer(AsmCode &asmCode);
        void optimize();
    private:
        bool checkCmdType(int i, AsmCmdType cmdType);
        bool checkOpType(int i, AsmOpType opType);
        bool checkOpTypeIsMovOrMovq(int i);
        bool checkOperand1Type(int i, AsmOperandType operandType);
        bool checkOperand2Type(int i, AsmOperandType operandType);
        bool checkRegType(AsmOperandPtr operand1, AsmOperandPtr operand2);
        bool checkRegType(AsmOperandPtr operand, AsmRegType reg);
        bool checkFreeReg(int command, AsmOperandPtr regOperand);
        bool checkAdressReg(AsmOperandPtr memory, AsmOperandPtr reg);
        int getIntImmediate(AsmOperandPtr operand);
        int getMemoryOffset(AsmOperandPtr operand);
        void deleteLabels();
        bool isJumpCmd(int i);
        std::string getJumpLabel(int i);
        AsmOperandPtr getOperand1(int i);
        AsmOperandPtr getOperand2(int i);
        void deleteCommands(int startPos, int count = 1);
        typedef std::function<bool(int)> optimizerFunction;
        std::vector<optimizerFunction> optimizerFunctions; 
        std::vector<int> optFuncStat;
        AsmCode &asmCode;
        std::vector<AsmCmdPtr> &commands;
};

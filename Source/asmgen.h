#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <stack>

enum AsmRegType {
    RAX,
    RBX,
    RCX,
    RDX,
    RBP,
    RSP,
    RSI,
    RDI,
    XMM0,
    XMM1,
};

enum AsmOpType {
    NONE,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    IMUL,
    IDIV,
    XOR,
    MOV,
    CALL,
    MOVQ,
    ADDSD,
    SUBSD,
    DIVSD,
    MULSD,
    CVTSI2SD,
    LABEL,
    CMP,
    JMP,
    JE,
    JNE,
    JL,
    JLE,
    JGE,
    JG,
    COMISD,
    JB,
    JBE,
    JAE,
    JA,
    TEST,
    JZ,
    JNZ,
    NEG,
    LEA,
    RET,
};

static std::map<AsmOpType, std::string> asmOpNames = {
        {PUSH, "push"},
        {POP, "pop"},
        {ADD, "add"},
        {SUB, "sub"},
        {MUL, "mul"},
        {IMUL, "imul"},
        {IDIV, "idiv"},
        {XOR, "xor"},
        {MOV, "mov"},
        {CALL, "call"},
        {MOVQ, "movq"},
        {ADDSD, "addsd"},
        {SUBSD, "subsd"},
        {DIVSD, "divsd"},
        {MULSD, "mulsd"},
        {CVTSI2SD, "cvtsi2sd"},
        {LABEL, "label"},
        {CMP, "cmp"},
        {JMP, "jmp"},
        {JE, "je"},
        {JNE, "jne"},
        {JL, "jl"},
        {JLE, "jle"},
        {JGE, "jge"},
        {JG, "jg"},
        {COMISD, "comisd"},
        {JA, "ja"},
        {JAE, "jae"},
        {JBE, "jbe"},
        {JB, "jb"},
        {TEST, "test"},
        {JZ, "jz"},
        {JNZ, "jnz"},
        {NEG, "neg"},
        {LEA, "lea"},
        {RET, "ret"},
};

static std::map<AsmRegType, std::string> asmRegNames = {
        {RAX, "rax"},
        {RBX, "rbx"},
        {RCX, "rcx"},
        {RDX, "rdx"},
        {RBP, "rbp"},
        {RSP, "rsp"},
        {RSI, "rsi"},
        {RDI, "rdi"},
        {XMM0, "xmm0"},
        {XMM1, "xmm1"},
};

enum class AsmCmdType {
    Cmd,
    Cmd0,
    Cmd1,
    Cmd2,
    Label,
};

enum class AsmOperandType {
    Operand,
    Reg,
    IntImmediate,
    StringImmediate,
    Memory,
};

class AsmOperand {
public:
    virtual std::string getString() = 0;
    virtual AsmOperandType getOperandType();
    virtual bool isImmediate();
};

typedef std::shared_ptr<AsmOperand> AsmOperandPtr;

class AsmCmd {
public:
    AsmCmd(AsmOpType opType, AsmOperandPtr operand1 = AsmOperandPtr(), AsmOperandPtr operand2 = AsmOperandPtr());
    virtual std::string getString();
    AsmOpType getOpType();
    virtual AsmCmdType getCmdType();
    AsmOperandPtr getOperand1();
    AsmOperandPtr getOperand2();
protected:
    AsmOpType opType;
    AsmOperandPtr operand1, operand2;
    
};

typedef std::shared_ptr<AsmCmd> AsmCmdPtr;

class AsmCmd0: public AsmCmd {
public:
    AsmCmd0(AsmOpType opType);
    std::string getString();
    AsmCmdType getCmdType() override;
};

class AsmCmd1: public AsmCmd {
public:
    AsmCmd1(AsmOpType opType, AsmOperandPtr operand);
    std::string getString();
    AsmCmdType getCmdType() override;
};

class  AsmCmd2: public AsmCmd {
public:
    AsmCmd2(AsmOpType opType, AsmOperandPtr operand1, AsmOperandPtr operand2);
    std::string getString();
    AsmCmdType getCmdType() override;
};

class AsmLabel: public AsmCmd {
public:
    AsmLabel(std::string name);
    std::string getString();
    AsmCmdType getCmdType() override;
private:
    std::string name;
};

class AsmReg: public AsmOperand {
public:
    AsmReg(AsmRegType reg);
    std::string getString();
    AsmOperandType getOperandType() override;
    AsmRegType getRegType();
private:
    AsmRegType reg;
};

class AsmImmediate: public AsmOperand {
public:
    bool isImmediate() override;
};

class AsmIntImmediate: public AsmImmediate {
public:
    AsmIntImmediate(int value);
    std::string getString();
    AsmOperandType getOperandType() override;
    int getValue();
private:
    int value;
};

class AsmStringImmediate: public AsmImmediate {
public:
    AsmStringImmediate(std::string value);
    std::string getString();
    AsmOperandType getOperandType() override;
private:
    std::string value;
};

class AsmMemory: public AsmOperand {
public:
    AsmMemory(std::string name, int offset = 0);
    AsmMemory(AsmRegType reg, int offset = 0);
    AsmMemory(const AsmMemory &adress);
    AsmMemory(AsmOperandPtr memoryOperand);
    std::string getString();
    AsmOperandType getOperandType() override;
    AsmOperandPtr getOperand();
    void clearSize();
    void addOffset(int value);
    int getOffset();
private:
    AsmOperandPtr operand;
    int offset;
    std::string size;
};

typedef std::shared_ptr<AsmMemory> AsmMemoryPtr;

class AsmData {
public:
    AsmData(std::string name);
    virtual std::string getString() = 0;
protected:
    std::string name;
};

typedef std::shared_ptr<AsmData> AsmDataPtr;

class AsmArrayData: public AsmData {
public:
    AsmArrayData(std::string name, int size);
    std::string getString() override;
private:
    int size;
};

class AsmFloatData: public AsmData {
public:
    AsmFloatData(std::string name, double value);
    std::string getString() override;
private:
    double value;
};

class AsmIntData: public AsmData {
public:
    AsmIntData(std::string name, int value);
    std::string getString() override;
private:
    int value;
};

class AsmStringData: public AsmData {
public:
    AsmStringData(std::string name, std::string value);
    std::string getString() override;
private:
    std::string value;
};

class AsmCode {
public:
    AsmCode();
    std::string getString();
    void addCmd(AsmOpType opType);
    void addCmd(AsmOpType opType, AsmRegType reg);
    void addCmd(AsmOpType opType, int value);
    void addCmd(AsmOpType opType, std::string value);
    void addCmd(AsmOpType opType, AsmOperandPtr operand);
    void addCmd(AsmOpType opType, AsmRegType destReg, AsmRegType sourceReg);
    void addCmd(AsmOpType opType, AsmRegType reg, std::string data);
    void addCmd(AsmOpType opType, AsmRegType reg, int value);
    void addCmd(AsmOpType opType, AsmOperandPtr operand, AsmRegType reg);
    void addCmd(AsmOpType opType, AsmRegType reg, AsmOperandPtr operand);
    void addWriteInt();
    void addWriteNewLine();
    void addWriteFloat();
    void addWriteString(std::string value);
    void addData(std::string name, std::string value);
    void addData(std::string name, int value);
    void addData(std::string name, double value);
    void addArrayData(std::string name, int size);
    void addLabel(std::string name);
    std::string getVarName(std::string name);
    std::string genVarName();
    std::string genLabelName();
    AsmOperandPtr getAdressOperand(std::string name, int offset = 0);
    AsmOperandPtr getAdressOperand(AsmRegType reg, int offset = 0);
    void addLabels(std::string nameContinue, std::string nameBreak);
    void deleteLabels();
    std::string getLabelContinue();
    std::string getLabelBreak();
    void addCmd(AsmCmdPtr cmd);
    std::vector<AsmCmdPtr> commands;
protected:
    void addWrite(std::string format);
    std::vector<AsmDataPtr> data;
    std::stack<std::string> labelsContinue;
    std::stack<std::string> labelsBreak;
    int namesCount;
    int pushCount;
    int labelsCount;
};

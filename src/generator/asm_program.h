#ifndef ASM_PROGRAM_H_INCLUDED
#define ASM_PROGRAM_H_INCLUDED

#include <vector>
#include <iostream>
#include "..\misc\smart_ptrs.h"

enum AsmOpcodeT {
	ASM_MOV,
	ASM_PUSH,
	ASM_POP,
	ASM_ADD,
	ASM_SUB,
	ASM_CALL,
	ASM_FLD,
	ASM_FILD,
	ASM_IMUL,
	ASM_IDIV,
	ASM_INC,
	ASM_DEC,
	ASM_FSTP,
	ASM_FISTP,
	ASM_FCHS,
	ASM_NEG,
	ASM_NOT,
	ASM_TEST,
	ASM_JMP,
	ASM_JZ,
	ASM_JNZ,
	ASM_JL,
	ASM_JLE,
	ASM_JG,
	ASM_JGE,
	ASM_JE,
	ASM_JNE,
	ASM_OR,
	ASM_XOR,
	ASM_AND,
	ASM_CMP,
	ASM_SHL,
	ASM_SHR,
	ASM_FMUL,
	ASM_FDIV,
	ASM_FIMUL,
	ASM_FIDIV,
	ASM_FIDIVR,
	ASM_FADD,
	ASM_FSUB,
	ASM_FIADD,
	ASM_FISUB,
	ASM_FISUBR,
	ASM_SETL,
	ASM_SETLE,
	ASM_SETG,
	ASM_SETGE,
	ASM_SETE,
	ASM_SETNE,
	ASM_SETZ,
	ASM_CDQ,
	ASM_NONE
};

extern const int ASM_OPCODES_NUMBER;
extern const char* ASM_OPCODES_STR[];

enum AsmRegT {
	ASM_EAX,
	ASM_EBX,
	ASM_ECX,
	ASM_EDX,
	ASM_ESP,
	ASM_EBP,
	ASM_BL,
	ASM_CL
};

extern const int ASM_REGS_NUMBER;
extern const char* ASM_REGS_STR[];

enum AsmSegT {
	ASM_SEG_DS,
	ASM_SEG_SS
};

enum AsmOpClass {
	ASM_OP_CLASS_INT_CONST,
	ASM_OP_CLASS_DATA,
	ASM_OP_CLASS_OFFSET_DATA,
	ASM_OP_CLASS_PROC,
	ASM_OP_CLASS_LBL,
	ASM_OP_CLASS_REG,
	ASM_OP_CLASS_REG_OFFSET,
	ASM_OP_CLASS_WORD_ZERO
};

struct AsmOp {
	virtual AsmOpClass GetAsmOpClass() const = 0;
	virtual bool IsEqual(AsmOp*) const = 0;
	virtual bool IsReg(AsmRegT) const { return false; }
	virtual bool IsIntConst(int) const { return false; }
	virtual void Output(std::ostream&) = 0;
};

struct AsmOpIntConst : public AsmOp {
	int value;
	AsmOpIntConst(int);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_INT_CONST; }
	bool IsEqual(AsmOp*) const;
	bool IsIntConst(int value1) const { return (value == value1); }
	void Output(std::ostream&);
};

struct AsmOpData : public AsmOp {
	std::string name;
	AsmOpData(const std::string&);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_DATA; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmOpOffsetData : public AsmOp {
	std::string name;
	AsmOpOffsetData(const std::string&);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_OFFSET_DATA; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmOpProc : public AsmOp {
	std::string name;
	AsmOpProc(const std::string&);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_PROC; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmOpLbl : public AsmOp {
	int num;
	AsmOpLbl(int);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_LBL; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmOpReg : public AsmOp {
	AsmRegT reg;
	AsmOpReg(AsmRegT);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_REG; }
	bool IsEqual(AsmOp*) const;
	bool IsReg(AsmRegT reg1) const { return (reg == reg1); }
	void Output(std::ostream&);
};

struct AsmOpRegOffset : public AsmOp {
	AsmSegT seg;
	AsmRegT reg;
	AsmOpRegOffset(AsmSegT, AsmRegT);
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_REG_OFFSET; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmOpWordZero : public AsmOp {
	AsmOpClass GetAsmOpClass() const { return ASM_OP_CLASS_WORD_ZERO; }
	bool IsEqual(AsmOp*) const;
	void Output(std::ostream&);
};

struct AsmCmdOrLbl {
	virtual bool IsLbl() const { return false; }
	virtual bool IsCmd(AsmOpcodeT) const { return false; }
	virtual void Output(std::ostream&) = 0;
};

struct AsmLbl : public AsmCmdOrLbl {
	int num;
	AsmLbl(int);
	bool IsLbl() const { return true; }
	void Output(std::ostream&);
};

enum AsmCmdClass {
	ASM_CMD_CLASS_0,
	ASM_CMD_CLASS_1,
	ASM_CMD_CLASS_2
};

struct AsmCmd : public AsmCmdOrLbl {
	AsmOpcodeT opcode;
	AsmCmd(AsmOpcodeT);
	bool IsCmd(AsmOpcodeT) const;
	void OutputOpcode(std::ostream&);
	virtual AsmCmdClass GetAsmCmdClass() const = 0;
};

struct AsmCmd_0 : public AsmCmd {
	AsmCmd_0(AsmOpcodeT);
	AsmCmdClass GetAsmCmdClass() const { return ASM_CMD_CLASS_0; }
	void Output(std::ostream&);
};

struct AsmCmd_1 : public AsmCmd {
	std::auto_ptr<AsmOp> op;
	AsmCmd_1(AsmOpcodeT, std::auto_ptr<AsmOp>);
	AsmCmdClass GetAsmCmdClass() const { return ASM_CMD_CLASS_1; }
	void Output(std::ostream&);
};

struct AsmCmd_2 : public AsmCmd {
	std::auto_ptr<AsmOp> op1;
	std::auto_ptr<AsmOp> op2;
	AsmCmd_2(AsmOpcodeT, std::auto_ptr<AsmOp>, std::auto_ptr<AsmOp>);
	AsmCmdClass GetAsmCmdClass() const { return ASM_CMD_CLASS_2; }
	void Output(std::ostream&);
};

struct AsmProc {
	struct LocalVar {
		std::string name;
		int size;
		LocalVar(const std::string& name, int size) : name(name), size(size) {}
	};
	typedef std::vector<std::string> Params;
	typedef std::vector<LocalVar> Locals;

	std::string name;
	bool is_void;
	Params params;
	Locals locals;
	ListP<AsmCmdOrLbl*> body;
	AsmProc(const std::string&, bool, Params&, Locals&);
	int GetEbpOffset(const std::string&);
	void Optimize();
	void Output(std::ostream&);
};

struct AsmDataSegment {
	std::vector<std::pair<std::string, int> > dd_dup_dirs;
	std::vector<double> dd_float_dirs;
	std::vector<std::string> db_string_dirs;
	void Output(std::ostream&);
};

class AsmProgram {
	AsmDataSegment data_segment;
	ListP<AsmProc*> proc_list;
	int lbl_cnt;
public:
	AsmProgram();
	void DirDdDup(std::string&, int);
	std::string DirDdFloat(double);
	std::string DirDbString(const std::string&);
	void Cmd(AsmOpcodeT);
	void Cmd(AsmOpcodeT, AsmOp*);
	void Cmd(AsmOpcodeT, AsmOp*, AsmOp*);
	void NewProc(const std::string&, bool, AsmProc::Params&, AsmProc::Locals&);
	int NewLbl();
	void Lbl(int);
	int GetEbpOffset(const std::string&);
	void Optimize();
	void Output(std::ostream&);
};

AsmOpReg* AsmReg(AsmRegT);
AsmOpRegOffset* AsmRegOffset(AsmSegT, AsmRegT);
AsmOpLbl* AsmLabel(int);
AsmOpIntConst* AsmIntConst(int);
AsmOpData* AsmData(const std::string&);
AsmOpOffsetData* AsmOffsetData(const std::string&);
AsmOpProc* AsmProcedure(const std::string&);
AsmOpWordZero* AsmWordZero();

const std::string PREFIX_GLOBAL_VAR = "g$";
const std::string PREFIX_LOCAL_VAR = "@@l$";
const std::string PREFIX_PARAMETER = "@@p$";
const std::string PREFIX_RESULT = "@@result";
const std::string PREFIX_REAL_CONST = "real_const$";
const std::string PREFIX_STRING_CONST = "string_const$";
const std::string PREFIX_FUNC = "f$";
const std::string PREFIX_LABEL = "lbl$";
const std::string PREFIX_EXIT = "@@lbl_exit";
const std::string FLOAT32 = "float32";
const int RETURN_ADDRESS_SIZE = 2;
const int EBP_SIZE = 4;

#endif // ASM_PROGRAM_H_INCLUDED

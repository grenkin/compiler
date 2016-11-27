#include <string>
#include "asm_program.h"

const int ASM_OPCODES_NUMBER = 51;
const char* ASM_OPCODES_STR[ASM_OPCODES_NUMBER] = {
	"mov", "push", "pop", "add", "sub", "call", "fld", "fild", "imul", "idiv",
	"inc", "dec", "fstp", "fistp", "fchs", "neg", "not", "test", "jmp", "jz",
	"jnz", "jl", "jle", "jg", "jge", "je", "jne", "or", "xor", "and", "cmp",
	"shl", "shr", "fmul", "fdiv", "fimul", "fidiv", "fidivr", "fadd", "fsub",
	"fiadd", "fisub", "fisubr", "setl", "setle", "setg", "setge", "sete",
	"setne", "setz", "cdq"
};

const int ASM_REGS_NUMBER = 8;
const char* ASM_REGS_STR[ASM_REGS_NUMBER] = {
	"eax", "ebx", "ecx", "edx", "esp", "ebp", "bl", "cl"
};

AsmOpIntConst::AsmOpIntConst(int value)
	: value(value)
{
}

bool AsmOpIntConst::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpIntConst*>(op)->value == value);
}

AsmOpData::AsmOpData(const std::string& name)
	: name(name)
{
}

bool AsmOpData::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpData*>(op)->name == name);
}

AsmOpOffsetData::AsmOpOffsetData(const std::string& name)
	: name(name)
{
}

bool AsmOpOffsetData::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpOffsetData*>(op)->name == name);
}

AsmOpProc::AsmOpProc(const std::string& name)
	: name(name)
{
}

bool AsmOpProc::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpProc*>(op)->name == name);
}

AsmOpLbl::AsmOpLbl(int num)
	: num(num)
{
}

bool AsmOpLbl::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpLbl*>(op)->num == num);
}

AsmOpReg::AsmOpReg(AsmRegT reg)
	: reg(reg)
{
}

bool AsmOpReg::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpReg*>(op)->reg == reg);
}

AsmOpRegOffset::AsmOpRegOffset(AsmSegT seg, AsmRegT reg)
	: seg(seg), reg(reg)
{
}

bool AsmOpRegOffset::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass() &&
		static_cast<AsmOpRegOffset*>(op)->seg == seg &&
		static_cast<AsmOpRegOffset*>(op)->reg == reg);
}

bool AsmOpWordZero::IsEqual(AsmOp* op) const
{
	return (op->GetAsmOpClass() == GetAsmOpClass());
}

AsmLbl::AsmLbl(int num)
	: num(num)
{
}

AsmCmd::AsmCmd(AsmOpcodeT opcode)
	: opcode(opcode)
{
}

bool AsmCmd::IsCmd(AsmOpcodeT opcode1) const
{
	return (opcode == opcode1);
}

AsmCmd_0::AsmCmd_0(AsmOpcodeT opcode)
	: AsmCmd(opcode)
{
}

AsmCmd_1::AsmCmd_1(AsmOpcodeT opcode, std::auto_ptr<AsmOp> op)
	: AsmCmd(opcode), op(op)
{
}

AsmCmd_2::AsmCmd_2(AsmOpcodeT opcode, std::auto_ptr<AsmOp> op1, std::auto_ptr<AsmOp> op2)
	: AsmCmd(opcode), op1(op1), op2(op2)
{
}

AsmProc::AsmProc(const std::string& name1, bool is_void1,
	Params& params1, Locals& locals1)
	: name(name1), is_void(is_void1), params(params1), locals(locals1)
{
}

int AsmProc::GetEbpOffset(const std::string& var_name)
{
	int params_size = 4*params.size();
	int locals_size = 0;
	for (Locals::iterator i = locals.begin(); i != locals.end(); ++i)
		locals_size += 4*i->size;
	int k = EBP_SIZE + locals_size + RETURN_ADDRESS_SIZE + params_size;
	for (Params::iterator i = params.begin(); i != params.end(); ++i) {		
		k -= 4;
		if (var_name == *i)
			return k;
	}
	k -= RETURN_ADDRESS_SIZE;
	for (Locals::iterator i = locals.begin(); i != locals.end(); ++i) {
		k -= 4*i->size;
		if (i->name == var_name)
			return k;
	}
}

AsmProgram::AsmProgram()
	: lbl_cnt(0)
{
}

void AsmProgram::DirDdDup(std::string& name, int size)
{
	data_segment.dd_dup_dirs.push_back(make_pair(name, size));
}

std::string AsmProgram::DirDdFloat(double value)
{
	data_segment.dd_float_dirs.push_back(value);
	std::string s = PREFIX_REAL_CONST;
	char buf[50];
	s += _itoa(data_segment.dd_float_dirs.size(), buf, 10);
	return s;
}

std::string AsmProgram::DirDbString(const std::string& value)
{
	data_segment.db_string_dirs.push_back(value);
	std::string s = PREFIX_STRING_CONST;
	char buf[50];
	s += _itoa(data_segment.db_string_dirs.size(), buf, 10);
	return s;
}

void AsmProgram::Cmd(AsmOpcodeT opcode)
{
	AsmCmd_0* p = new AsmCmd_0(opcode);
	proc_list.back()->body.PushBack(std::auto_ptr<AsmCmdOrLbl>(p));
}

void AsmProgram::Cmd(AsmOpcodeT opcode, AsmOp* op)
{
	AsmCmd_1* p = new AsmCmd_1(opcode, std::auto_ptr<AsmOp>(op));
	proc_list.back()->body.PushBack(std::auto_ptr<AsmCmdOrLbl>(p));
}

void AsmProgram::Cmd(AsmOpcodeT opcode, AsmOp* op1, AsmOp* op2)
{
	AsmCmd_2* p = new AsmCmd_2(
		opcode,	std::auto_ptr<AsmOp>(op1), std::auto_ptr<AsmOp>(op2));
	proc_list.back()->body.PushBack(std::auto_ptr<AsmCmdOrLbl>(p));
}

void AsmProgram::NewProc(const std::string& name, bool is_void,
	AsmProc::Params& params, AsmProc::Locals& locals)
{
	proc_list.PushBack(std::auto_ptr<AsmProc>(new AsmProc(name, is_void, params, locals)));
}

int AsmProgram::NewLbl()
{
	return ++lbl_cnt;
}

void AsmProgram::Lbl(int num)
{
	AsmLbl* p = new AsmLbl(num);
	proc_list.back()->body.PushBack(std::auto_ptr<AsmCmdOrLbl>(p));
}

int AsmProgram::GetEbpOffset(const std::string& var_name)
{
	return proc_list.back()->GetEbpOffset(var_name);
}

AsmOpReg* AsmReg(AsmRegT reg)
{
	return new AsmOpReg(reg);
}

AsmOpRegOffset* AsmRegOffset(AsmSegT seg, AsmRegT reg)
{
	return new AsmOpRegOffset(seg, reg);
}

AsmOpLbl* AsmLabel(int num)
{
	return new AsmOpLbl(num);
}

AsmOpIntConst* AsmIntConst(int value)
{
	return new AsmOpIntConst(value);
}

AsmOpData* AsmData(const std::string& name)
{
	return new AsmOpData(name);
}

AsmOpOffsetData* AsmOffsetData(const std::string& name)
{
	return new AsmOpOffsetData(name);
}

AsmOpProc* AsmProcedure(const std::string& name)
{
	return new AsmOpProc(name);
}

AsmOpWordZero* AsmWordZero()
{
	return new AsmOpWordZero();
}

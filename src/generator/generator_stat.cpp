#include "..\parser\stat.h"
#include "..\errors\errors.h"

namespace {

	std::vector<std::pair<int, int> > loops_labels;

}

void ExpStat::Generate(AsmProgram& asm_program) const
{
	GenerateExp(exp.get(), asm_program);
}

void CompoundStat::Generate(AsmProgram& asm_program) const
{
	Generate(false, asm_program);
}

void CompoundStat::Generate(bool func_body, AsmProgram& asm_program) const
{
	if (!func_body) {
		if (!sym_table.scope1.empty())
			throw GeneratorError("A block contains declarations of variables");
	}
	for (StatList::const_iterator i = stat_list.begin(); i != stat_list.end(); ++i)
		(*i)->Generate(asm_program);
}

void SelectionStat::Generate(AsmProgram& asm_program) const
{
	exp->Generate(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
	int lbl1 = asm_program.NewLbl();
	asm_program.Cmd(ASM_JZ, AsmLabel(lbl1));
	stat1->Generate(asm_program);
	int lbl2;
	if (stat2.get()) {
		lbl2 = asm_program.NewLbl();
		asm_program.Cmd(ASM_JMP, AsmLabel(lbl2));
	}
	asm_program.Lbl(lbl1);
	if (stat2.get()) {
		stat2->Generate(asm_program);
		asm_program.Lbl(lbl2);
	}
}

void IterationStatWhile::Generate(AsmProgram& asm_program) const
{
	int lbl1 = asm_program.NewLbl();
	asm_program.Lbl(lbl1);
	exp->Generate(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
	int lbl2 = asm_program.NewLbl();
	asm_program.Cmd(ASM_JZ, AsmLabel(lbl2));
	loops_labels.push_back(std::make_pair(lbl1, lbl2));
	stat->Generate(asm_program);
	loops_labels.pop_back();
	asm_program.Cmd(ASM_JMP, AsmLabel(lbl1));
	asm_program.Lbl(lbl2);
}

void IterationStatDoWhile::Generate(AsmProgram& asm_program) const
{
	int lbl1 = asm_program.NewLbl();
	asm_program.Lbl(lbl1);
	int lbl2 = asm_program.NewLbl();
	loops_labels.push_back(std::make_pair(lbl1, lbl2));
	stat->Generate(asm_program);
	loops_labels.pop_back();
	exp->Generate(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_JZ, AsmLabel(lbl2));
	asm_program.Cmd(ASM_JMP, AsmLabel(lbl1));
	asm_program.Lbl(lbl2);
}

void IterationStatFor::Generate(AsmProgram& asm_program) const
{
	GenerateExp(exp1.get(), asm_program);
	int lbl1 = asm_program.NewLbl();
	asm_program.Lbl(lbl1);
	int lbl2 = asm_program.NewLbl();
	loops_labels.push_back(std::make_pair(lbl1, lbl2));
	stat->Generate(asm_program);
	loops_labels.pop_back();
	GenerateExp(exp3.get(), asm_program);
	if (exp2.get()) {
		exp2->Generate(asm_program);
		asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
		asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
		asm_program.Cmd(ASM_JZ, AsmLabel(lbl2));
	}
	asm_program.Cmd(ASM_JMP, AsmLabel(lbl1));
	asm_program.Lbl(lbl2);
}

void JumpStatContinue::Generate(AsmProgram& asm_program) const
{
	if (loops_labels.empty())
		throw GeneratorError("continue is not inside a loop");
	asm_program.Cmd(ASM_JMP, AsmLabel(loops_labels.back().first));
}

void JumpStatBreak::Generate(AsmProgram& asm_program) const
{
	if (loops_labels.empty())
		throw GeneratorError("break is not inside a loop");
	asm_program.Cmd(ASM_JMP, AsmLabel(loops_labels.back().second));
}

void JumpStatReturn::Generate(AsmProgram& asm_program) const
{
	if (exp.get()) {
		exp->Generate(asm_program);
		asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
		asm_program.Cmd(ASM_MOV, AsmData(PREFIX_RESULT), AsmReg(ASM_EAX));
	}
	asm_program.Cmd(ASM_JMP, AsmData(PREFIX_EXIT));
}

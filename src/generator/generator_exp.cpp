#include "..\parser\tr_unit.h"

namespace {

	std::string get_var_str(const std::string& name, DeclVarClass decl_var_class)
	{
		std::string s = name;
		switch (decl_var_class) {
			case DECL_VAR_CLASS_GLOBAL:
				s = PREFIX_GLOBAL_VAR + s;
				break;
			case DECL_VAR_CLASS_LOCAL:
				s = PREFIX_LOCAL_VAR + s;
				break;
			case DECL_VAR_CLASS_PARAM:
				s = PREFIX_PARAMETER + s;
				break;
		}
		return s;
	}

}

void Exp::Generate(AsmProgram& asm_program) const
{
	for (ListP<ExprNode*>::const_iterator i = assignment_exp_list.begin();
		++i != assignment_exp_list.end();)
	{
		GenerateExp(*i, asm_program);
	}
	assignment_exp_list.back()->Generate(asm_program);
}

AsmSegT Exp::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

AsmSegT AssignmentExp::InternalGenerate(AsmProgram& asm_program) const
{
	AsmSegT seg = unary_exp->GenerateAddr(asm_program);
	assignment_exp->Generate(asm_program);
	if (unary_exp->expr_type.IsIntegral() && assignment_exp->expr_type.IsFloat()) {
		asm_program.Cmd(ASM_FLD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
		asm_program.Cmd(ASM_FISTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
	}
	else if (unary_exp->expr_type.IsFloat() && assignment_exp->expr_type.IsIntegral()) {
		asm_program.Cmd(ASM_FILD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
		asm_program.Cmd(ASM_FSTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
	}
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_MOV, AsmRegOffset(seg, ASM_EAX), AsmReg(ASM_EBX));
	return seg;
}

void AssignmentExp::Generate(AsmProgram& asm_program) const
{
	AsmSegT seg = InternalGenerate(asm_program);
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EBX));
}

AsmSegT AssignmentExp::GenerateAddr(AsmProgram& asm_program) const
{
	AsmSegT seg = InternalGenerate(asm_program);
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
	return seg;
}

void ConditionalExp::Generate(AsmProgram& asm_program) const
{
	conditional_exp->Generate(asm_program);
	exp->Generate(asm_program);
	logical_or_exp->Generate(asm_program);
	int lbl1 = asm_program.NewLbl();
	int lbl2 = asm_program.NewLbl();
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
	asm_program.Cmd(ASM_POP, AsmReg(ASM_ECX));
	asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_JZ, AsmLabel(lbl1));
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EBX));
	asm_program.Cmd(ASM_JMP, AsmLabel(lbl2));
	asm_program.Lbl(lbl1);
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_ECX));
	asm_program.Lbl(lbl2);
}

AsmSegT ConditionalExp::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void BinaryExp::Generate(AsmProgram& asm_program) const
{
	switch (binary_exp_class) {
		int lbl1, lbl2;
		case BINARY_EXP_CLASS_LOGICAL_OR:
			lbl1 = asm_program.NewLbl();
			lbl2 = asm_program.NewLbl();
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_JNZ, AsmLabel(lbl1));
			arg2->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_JNZ, AsmLabel(lbl1));
			asm_program.Cmd(ASM_PUSH, AsmIntConst(0));
			asm_program.Cmd(ASM_JMP, AsmLabel(lbl2));
			asm_program.Lbl(lbl1);
			asm_program.Cmd(ASM_PUSH, AsmIntConst(1));
			asm_program.Lbl(lbl2);
			break;
		case BINARY_EXP_CLASS_LOGICAL_AND:
			lbl1 = asm_program.NewLbl();
			lbl2 = asm_program.NewLbl();
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_JZ, AsmLabel(lbl1));
			arg2->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_JZ, AsmLabel(lbl1));
			asm_program.Cmd(ASM_PUSH, AsmIntConst(1));
			asm_program.Cmd(ASM_JMP, AsmLabel(lbl2));
			asm_program.Lbl(lbl1);
			asm_program.Cmd(ASM_PUSH, AsmIntConst(0));
			asm_program.Lbl(lbl2);
			break;
		case BINARY_EXP_CLASS_INCLUSIVE_OR:
			arg2->Generate(asm_program);
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_OR, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			break;
		case BINARY_EXP_CLASS_EXCLUSIVE_OR:
			arg2->Generate(asm_program);
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_XOR, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			break;
		case BINARY_EXP_CLASS_AND:
			arg2->Generate(asm_program);
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_AND, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			break;
		case BINARY_EXP_CLASS_EQUALITY:
		case BINARY_EXP_CLASS_RELATIONAL:
			arg2->Generate(asm_program);
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_XOR, AsmReg(ASM_ECX), AsmReg(ASM_ECX));
			asm_program.Cmd(ASM_CMP, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
			switch (op) {
				case OP_LESS:
					asm_program.Cmd(ASM_SETL, AsmReg(ASM_CL));
					break;
				case OP_LESS_EQUAL:
					asm_program.Cmd(ASM_SETLE, AsmReg(ASM_CL));
					break;
				case OP_MORE:
					asm_program.Cmd(ASM_SETG, AsmReg(ASM_CL));
					break;
				case OP_MORE_EQUAL:
					asm_program.Cmd(ASM_SETGE, AsmReg(ASM_CL));
					break;
				case OP_EQUAL_EQUAL:
					asm_program.Cmd(ASM_SETE, AsmReg(ASM_CL));
					break;
				case OP_EXCL_MARK_EQUAL:
					asm_program.Cmd(ASM_SETNE, AsmReg(ASM_CL));
					break;
			}
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_ECX));
			break;
		case BINARY_EXP_CLASS_SHIFT:
			arg2->Generate(asm_program);
			arg1->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
			asm_program.Cmd(ASM_MOV, AsmReg(ASM_CL), AsmReg(ASM_BL));
			if (op == OP_LESS_LESS)
				asm_program.Cmd(ASM_SHL, AsmReg(ASM_EAX), AsmReg(ASM_CL));
			else
				asm_program.Cmd(ASM_SHR, AsmReg(ASM_EAX), AsmReg(ASM_CL));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			break;
		case BINARY_EXP_CLASS_ADDITIVE:
		case BINARY_EXP_CLASS_MULT:
			if (arg1->expr_type.IsFloat() && arg2->expr_type.IsFloat()) {
				arg2->Generate(asm_program);
				arg1->Generate(asm_program);
				asm_program.Cmd(ASM_FLD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				asm_program.Cmd(ASM_ADD, AsmReg(ASM_ESP), AsmIntConst(4));
				asm_program.Cmd(ASM_FLD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				asm_program.Cmd(ASM_ADD, AsmReg(ASM_ESP), AsmIntConst(4));
				if (op == OP_STAR)
					asm_program.Cmd(ASM_FMUL);
				else if (op == OP_SLASH)
					asm_program.Cmd(ASM_FDIV);
				else if (op == OP_PLUS)
					asm_program.Cmd(ASM_FADD);
				else if (op == OP_MINUS)
					asm_program.Cmd(ASM_FSUB);
				asm_program.Cmd(ASM_SUB, AsmReg(ASM_ESP), AsmIntConst(4));
				asm_program.Cmd(ASM_FSTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
			}
			else if (arg1->expr_type.IsFloat() || arg2->expr_type.IsFloat()) {
				bool flag = false;
				if (arg1->expr_type.IsFloat()) {
					arg2->Generate(asm_program);
					arg1->Generate(asm_program);
				}
				else {
					arg1->Generate(asm_program);
					arg2->Generate(asm_program);
					flag = true;
				}
				asm_program.Cmd(ASM_FLD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				asm_program.Cmd(ASM_ADD, AsmReg(ASM_ESP), AsmIntConst(4));
				if (op == OP_STAR)
					asm_program.Cmd(ASM_FIMUL, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				else if (op == OP_SLASH) {
					if (flag)
						asm_program.Cmd(ASM_FIDIVR, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
					else
						asm_program.Cmd(ASM_FIDIV, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				}
				else if (op == OP_PLUS)
					asm_program.Cmd(ASM_FIADD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				else if (op == OP_MINUS) {
					if (flag)
						asm_program.Cmd(ASM_FISUBR, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
					else
						asm_program.Cmd(ASM_FISUB, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				}
				asm_program.Cmd(ASM_FSTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
			}
			else {
				arg2->Generate(asm_program);
				arg1->Generate(asm_program);		
				asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
				asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
				if (op == OP_STAR) {
					asm_program.Cmd(ASM_IMUL, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
					asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
				}
				else if (op == OP_SLASH) {
					asm_program.Cmd(ASM_CDQ);
					asm_program.Cmd(ASM_IDIV, AsmReg(ASM_EBX));
					asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
				}
				else if (op == OP_PERCENT) {
					asm_program.Cmd(ASM_CDQ);
					asm_program.Cmd(ASM_IDIV, AsmReg(ASM_EBX));
					asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EDX));
				}
				else if (op == OP_PLUS) {
					asm_program.Cmd(ASM_ADD, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
					asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
				}
				else if (op == OP_MINUS) {
					asm_program.Cmd(ASM_SUB, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
					asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
				}
			}
			break;
	}
}

AsmSegT BinaryExp::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void UnaryExpIncDec::Generate(AsmProgram& asm_program) const
{
	AsmSegT seg = unary_exp->GenerateAddr(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	if (inc_dec_operator == OP_PLUS_PLUS)
		asm_program.Cmd(ASM_INC, AsmRegOffset(seg, ASM_EAX));
	else
		asm_program.Cmd(ASM_DEC, AsmRegOffset(seg, ASM_EAX));
	asm_program.Cmd(ASM_PUSH, AsmRegOffset(seg, ASM_EAX));
}

AsmSegT UnaryExpIncDec::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void UnaryExpUnaryOperator::Generate(AsmProgram& asm_program) const
{
	switch (unary_operator) {
		case OP_AMP:
			unary_exp->GenerateAddr(asm_program);
			break;
		case OP_STAR:
			unary_exp->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_PUSH, AsmRegOffset(ASM_SEG_SS, ASM_EAX));
			/*
			При разыменовании указателя считается, что сегмент == ss.
			Поэтому глобальные переменные нельзя передавать по адресу.
			*/
			break;
		case OP_PLUS:
			unary_exp->Generate(asm_program);
			break;
		case OP_MINUS:
			unary_exp->Generate(asm_program);
			if (unary_exp->expr_type.IsIntegral()) {
				asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
				asm_program.Cmd(ASM_NEG, AsmReg(ASM_EAX));
				asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			}
			else {
				asm_program.Cmd(ASM_POP, AsmData(FLOAT32));
				asm_program.Cmd(ASM_FLD, AsmData(FLOAT32));
				asm_program.Cmd(ASM_FCHS);
				asm_program.Cmd(ASM_FSTP, AsmData(FLOAT32));
				asm_program.Cmd(ASM_PUSH, AsmData(FLOAT32));
			}
			break;
		case OP_SQUIGGLE:
			unary_exp->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_NOT, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
			break;
		case OP_EXCL_MARK:
			unary_exp->Generate(asm_program);
			asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_XOR, AsmReg(ASM_ECX), AsmReg(ASM_ECX));
			asm_program.Cmd(ASM_TEST, AsmReg(ASM_EAX), AsmReg(ASM_EAX));
			asm_program.Cmd(ASM_SETZ, AsmReg(ASM_CL));
			asm_program.Cmd(ASM_PUSH, AsmReg(ASM_ECX));
			break;
	}
}

AsmSegT UnaryExpUnaryOperator::GenerateAddr(AsmProgram& asm_program) const
{
	if (unary_operator == OP_STAR)
		unary_exp->Generate(asm_program);
	return ASM_SEG_SS;
}

AsmSegT PostfixExpArrayIndex::InternalGenerate(AsmProgram& asm_program) const
{
	ExprType expr_type2;
	if (postfix_exp->expr_type.IsPointer()) {
		exp->Generate(asm_program);
		postfix_exp->Generate(asm_program);
		expr_type2 = postfix_exp->expr_type.GetPointerType();
	}
	else {
		postfix_exp->Generate(asm_program);
		exp->Generate(asm_program);
		expr_type2 = exp->expr_type.GetPointerType();
	}
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EBX));
	asm_program.Cmd(ASM_IMUL, AsmReg(ASM_EBX), AsmIntConst(4*expr_type2.GetSize()));
	asm_program.Cmd(ASM_ADD, AsmReg(ASM_EAX), AsmReg(ASM_EBX));
	return ASM_SEG_SS;
}

void PostfixExpArrayIndex::Generate(AsmProgram& asm_program) const
{
	AsmSegT seg = InternalGenerate(asm_program);
	asm_program.Cmd(ASM_PUSH, AsmRegOffset(seg, ASM_EAX));
}

AsmSegT PostfixExpArrayIndex::GenerateAddr(AsmProgram& asm_program) const
{
	AsmSegT seg = InternalGenerate(asm_program);
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
	return seg;
}

void PostfixExpFuncCall::Generate(AsmProgram& asm_program) const
{
	if (postfix_exp->GetExprNodeClass() == EXPR_NODE_CLASS_PRIMARY_EXP) {
		PrimaryExp* p = static_cast<PrimaryExp*>(postfix_exp.get());
		if (p->GetPrimaryExpClass() == PRIMARY_EXP_CLASS_FUNC) {
			DeclFunc* decl_func = static_cast<PrimaryExpFunc*>(p)->decl_func;
			FunctionDefinition* fd = decl_func->func_def;
			if (!fd->result_type.IsVoid())
				asm_program.Cmd(ASM_SUB, AsmReg(ASM_ESP), AsmIntConst(4));
			ParamList::const_iterator j = fd->param_list.begin();
			for (ArgumentExpList::const_iterator i = argument_exp_list.begin();
				i != argument_exp_list.end(); ++i, ++j)
			{
				(*i)->Generate(asm_program);
				if ((*i)->expr_type.IsFloat() &&
					(*j)->type.IsIntegral())
				{
					asm_program.Cmd(ASM_FLD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
					asm_program.Cmd(ASM_FISTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				}
				else if ((*i)->expr_type.IsIntegral() &&
					(*j)->type.IsFloat())
				{
					asm_program.Cmd(ASM_FILD, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
					asm_program.Cmd(ASM_FSTP, AsmRegOffset(ASM_SEG_SS, ASM_ESP));
				}
			}
			asm_program.Cmd(ASM_CALL, AsmProcedure(fd->name));
		}
	}
}

AsmSegT PostfixExpFuncCall::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

AsmSegT PostfixExpPoint::InternalGenerate(AsmProgram& asm_program) const
{
	AsmSegT seg = postfix_exp->GenerateAddr(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_ADD, AsmReg(ASM_EAX),
		AsmIntConst(4*struct_decl->offset));
	return seg;
}

void PostfixExpPoint::Generate(AsmProgram& asm_program) const
{
	if (struct_decl->type.IsArray())
		GenerateAddr(asm_program);
	else {
		AsmSegT seg = InternalGenerate(asm_program);
		asm_program.Cmd(ASM_PUSH, AsmRegOffset(seg, ASM_EAX));
	}
}

AsmSegT PostfixExpPoint::GenerateAddr(AsmProgram& asm_program) const
{
	AsmSegT seg = InternalGenerate(asm_program);
	asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
	return seg;
}

void PostfixExpIncDec::Generate(AsmProgram& asm_program) const
{
	AsmSegT seg = postfix_exp->GenerateAddr(asm_program);
	asm_program.Cmd(ASM_POP, AsmReg(ASM_EAX));
	asm_program.Cmd(ASM_PUSH, AsmRegOffset(seg, ASM_EAX));
	if (inc_dec_operator == OP_PLUS_PLUS)
		asm_program.Cmd(ASM_INC, AsmRegOffset(seg, ASM_EAX));
	else
		asm_program.Cmd(ASM_DEC, AsmRegOffset(seg, ASM_EAX));
}

AsmSegT PostfixExpIncDec::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void PrimaryExpVar::Generate(AsmProgram& asm_program) const
{
	if (decl_var->type.IsArray())
		GenerateAddr(asm_program);
	else
		asm_program.Cmd(ASM_PUSH, AsmData(get_var_str(
			name, decl_var->decl_var_class)));
}

AsmSegT PrimaryExpVar::GenerateAddr(AsmProgram& asm_program) const
{
	if (decl_var->decl_var_class == DECL_VAR_CLASS_GLOBAL) {
		asm_program.Cmd(ASM_PUSH, AsmWordZero());
		asm_program.Cmd(ASM_PUSH, AsmOffsetData(get_var_str(
			name, DECL_VAR_CLASS_GLOBAL)));
		return ASM_SEG_DS;
	}
	else {
		int k = asm_program.GetEbpOffset(name);
		asm_program.Cmd(ASM_MOV, AsmReg(ASM_EAX), AsmReg(ASM_EBP));
		asm_program.Cmd(ASM_ADD, AsmReg(ASM_EAX), AsmIntConst(k));
		asm_program.Cmd(ASM_PUSH, AsmReg(ASM_EAX));
		return ASM_SEG_SS;
	}
}

void PrimaryExpFunc::Generate(AsmProgram& asm_program) const
{
}

AsmSegT PrimaryExpFunc::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void PrimaryExpIntConst::Generate(AsmProgram& asm_program) const
{ 
	asm_program.Cmd(ASM_PUSH, AsmIntConst(const_value));
}

AsmSegT PrimaryExpIntConst::GenerateAddr(AsmProgram& asm_program) const
{ 
	return ASM_SEG_DS;
}

void PrimaryExpRealConst::Generate(AsmProgram& asm_program) const
{
	std::string s = asm_program.DirDdFloat(const_value);
	asm_program.Cmd(ASM_PUSH, AsmData(s));
}

AsmSegT PrimaryExpRealConst::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void PrimaryExpStringConst::Generate(AsmProgram& asm_program) const
{
	std::string s = asm_program.DirDbString(const_value);
	asm_program.Cmd(ASM_PUSH, AsmWordZero());
	asm_program.Cmd(ASM_PUSH, AsmOffsetData(s));		
}

AsmSegT PrimaryExpStringConst::GenerateAddr(AsmProgram& asm_program) const
{
	return ASM_SEG_DS;
}

void GenerateExp(ExprNode* exp, AsmProgram& asm_program)
{
	if (exp) {
		exp->Generate(asm_program);
		if (!exp->expr_type.IsVoid())
			asm_program.Cmd(ASM_ADD, AsmReg(ASM_ESP), AsmIntConst(4));
	}
}

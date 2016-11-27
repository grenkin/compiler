#include "..\generator\asm_program.h"

#include <fstream>

namespace {

	bool are_operands_equal(std::auto_ptr<AsmOp>& op1, std::auto_ptr<AsmOp>& op2)
	{
		return (op1->GetAsmOpClass() == op2->GetAsmOpClass() && op1->IsEqual(op2.get()));
	}

	bool compare_reg_reg_offset(std::auto_ptr<AsmOp>& op1, std::auto_ptr<AsmOp>& op2)
	{
		return (
			op1->GetAsmOpClass() == ASM_OP_CLASS_REG &&
			op2->GetAsmOpClass() == ASM_OP_CLASS_REG_OFFSET &&
			static_cast<AsmOpReg*>(op1.get())->reg ==
			static_cast<AsmOpRegOffset*>(op2.get())->reg);
	}

	bool are_operands_alike(std::auto_ptr<AsmOp>& op1, std::auto_ptr<AsmOp>& op2)
	{
		return (are_operands_equal(op1, op2) ||
			compare_reg_reg_offset(op1, op2) ||
			compare_reg_reg_offset(op2, op1));
	}

	bool is_push32(AsmCmdOrLbl* p)
	{
		if (!p->IsCmd(ASM_PUSH))
			return false;
		AsmOpClass op_class = static_cast<AsmCmd_1*>(p)->op->GetAsmOpClass();
		return (op_class != ASM_OP_CLASS_WORD_ZERO &&
			op_class != ASM_OP_CLASS_OFFSET_DATA);
	}

	bool get_2_cmd_or_lbl(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i,
		AsmCmdOrLbl*& p1, AsmCmdOrLbl*& p2)
	{
		ListP<AsmCmdOrLbl*>::iterator j = i;
		if (j == body.end())
			return false;
		p1 = *j;
		++j;
		if (j == body.end())
			return false;
		p2 = *j;
		return true;
	}

	void erase_k_cmd_or_lbl(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i, int k)
	{
		for (int j = 0; j < k; ++j)
			i = body.Erase(i);
	}

	void erase_1_cmd_or_lbl(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		erase_k_cmd_or_lbl(body, i, 1);
	}

	void erase_2_cmd_or_lbl(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		erase_k_cmd_or_lbl(body, i, 2);
	}

	void insert_cmd_1(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i,
		AsmOpcodeT opcode, AsmOp* op)
	{
		AsmCmd_1* p = new AsmCmd_1(opcode, std::auto_ptr<AsmOp>(op));
		body.Insert(i, std::auto_ptr<AsmCmdOrLbl>(p));
	}

	void insert_cmd_2(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i,
		AsmOpcodeT opcode, AsmOp* op1, AsmOp* op2)
	{
		AsmCmd_2* p = new AsmCmd_2(
			opcode,	std::auto_ptr<AsmOp>(op1), std::auto_ptr<AsmOp>(op2));
		body.Insert(i, std::auto_ptr<AsmCmdOrLbl>(p));
	}

	void swap_2_cmd_or_lbl(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl* p = *i;
		*i = 0;
		ListP<AsmCmdOrLbl*>::iterator j = i;
		++j;
		++j;
		body.Insert(j, std::auto_ptr<AsmCmdOrLbl>(p));
		erase_1_cmd_or_lbl(body, i);		
	}

	bool is_stack_op(std::auto_ptr<AsmOp>& op)
	{
		return (op->GetAsmOpClass() == ASM_OP_CLASS_REG_OFFSET &&
			static_cast<AsmOpRegOffset*>(op.get())->reg == ASM_ESP ||
			op->IsReg(ASM_ESP));
	}

	bool can_exchange_with_push(AsmCmdOrLbl* p)
	{
		const int CMD_LIST_SIZE = 20;
		const AsmOpcodeT cmd_list[CMD_LIST_SIZE] = {
			ASM_POP, ASM_PUSH, ASM_CALL, ASM_JMP, ASM_JZ, ASM_JNZ, ASM_JL,
			ASM_JLE, ASM_JG, ASM_JGE, ASM_JE, ASM_JNE, ASM_CMP, ASM_SETL,
			ASM_SETLE, ASM_SETG, ASM_SETGE,	ASM_SETE, ASM_SETNE, ASM_SETZ
		};
		if (p->IsLbl())
			return false;
		for (int i = 0; i < CMD_LIST_SIZE; ++i) {
			if (p->IsCmd(cmd_list[i]))
				return false;
		}
		if (static_cast<AsmCmd*>(p)->GetAsmCmdClass() == ASM_CMD_CLASS_1) {
			if (is_stack_op(static_cast<AsmCmd_1*>(p)->op))
				return false;
		}
		else if (static_cast<AsmCmd*>(p)->GetAsmCmdClass() == ASM_CMD_CLASS_2) {
			if (is_stack_op(static_cast<AsmCmd_2*>(p)->op1) ||
				is_stack_op(static_cast<AsmCmd_2*>(p)->op2))
			{
				return false;
			}
		}
		return true;
	}

	bool has_op(AsmCmd* p, std::auto_ptr<AsmOp>& op)
	{
		switch (p->GetAsmCmdClass()) {
			case ASM_CMD_CLASS_0:
				return true;
				break;
			case ASM_CMD_CLASS_1:
				return are_operands_alike(static_cast<AsmCmd_1*>(p)->op, op);
				break;
			case ASM_CMD_CLASS_2:
				return (are_operands_alike(static_cast<AsmCmd_2*>(p)->op1, op) ||
					are_operands_alike(static_cast<AsmCmd_2*>(p)->op2, op));
				break;
		}
	}

	bool opt1(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (is_push32(p1) && p2->IsCmd(ASM_POP)) {
				if (!are_operands_equal(
					static_cast<AsmCmd_1*>(p1)->op,
					static_cast<AsmCmd_1*>(p2)->op))
				{
					if (static_cast<AsmCmd_1*>(p1)->op->GetAsmOpClass() !=
						ASM_OP_CLASS_REG &&
						static_cast<AsmCmd_1*>(p2)->op->GetAsmOpClass() !=
						ASM_OP_CLASS_REG)
					{
						return false;
					}
					insert_cmd_2(body, i, ASM_MOV,
						static_cast<AsmCmd_1*>(p2)->op.release(),
						static_cast<AsmCmd_1*>(p1)->op.release());
				}
				erase_2_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

	bool opt2(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (is_push32(p1) &&
				p2->IsCmd(ASM_ADD) &&
				static_cast<AsmCmd_2*>(p2)->op1->IsReg(ASM_ESP) &&
				static_cast<AsmCmd_2*>(p2)->op2->IsIntConst(4))
			{
				erase_2_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

	bool opt3(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (is_push32(p1) && can_exchange_with_push(p2) &&
				(static_cast<AsmCmd_1*>(p1)->op->GetAsmOpClass() ==
					ASM_OP_CLASS_INT_CONST ||
					!has_op(static_cast<AsmCmd*>(p2),
						static_cast<AsmCmd_1*>(p1)->op)))
			{
				swap_2_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

	bool opt4(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (p1->IsCmd(ASM_MOV) && !p2->IsLbl() &&
				static_cast<AsmCmd*>(p2)->GetAsmCmdClass() == ASM_CMD_CLASS_2 &&
				!p2->IsCmd(ASM_SHL) && !p2->IsCmd(ASM_SHR) &&
				!p2->IsCmd(ASM_TEST) && !p2->IsCmd(ASM_CMP) &&
				are_operands_equal(static_cast<AsmCmd_2*>(p1)->op1,
					static_cast<AsmCmd_2*>(p2)->op2) &&
				(static_cast<AsmCmd_2*>(p2)->op1->GetAsmOpClass() == ASM_OP_CLASS_REG ||
				static_cast<AsmCmd_2*>(p1)->op2->GetAsmOpClass() == ASM_OP_CLASS_REG))
			{
				AsmOp* q = static_cast<AsmCmd_2*>(p1)->op2.release();
				static_cast<AsmCmd_2*>(p2)->op2.reset(q);
				erase_1_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

	bool opt5(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		if ((*i)->IsCmd(ASM_ADD) || (*i)->IsCmd(ASM_SUB) ||
			(*i)->IsCmd(ASM_IMUL))
		{
			AsmCmd_2* p = static_cast<AsmCmd_2*>(*i);
			if (p->op2->GetAsmOpClass() == ASM_OP_CLASS_INT_CONST &&
				static_cast<AsmOpIntConst*>(p->op2.get())->value == 1)
			{
				AsmOpcodeT cmd = ASM_NONE;
				AsmOpcodeT cmd0 = static_cast<AsmCmd_2*>(*i)->opcode;
				switch (cmd0) {
					case ASM_ADD:
						cmd = ASM_INC;
						break;
					case ASM_SUB:
						cmd = ASM_DEC;
						break;
				}
				if (cmd != ASM_NONE) {
					insert_cmd_1(body, i, cmd,
						static_cast<AsmCmd_2*>(p)->op1.release());
				}
				erase_1_cmd_or_lbl(body, i);
				return true;
			}			
		}
		return false;
	}

	bool opt6(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (p1->IsCmd(ASM_FSTP) && p2->IsCmd(ASM_FLD) &&
				are_operands_equal(
					static_cast<AsmCmd_1*>(p1)->op,
					static_cast<AsmCmd_1*>(p2)->op))
			{
				erase_2_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

	bool opt7(ListP<AsmCmdOrLbl*>& body, ListP<AsmCmdOrLbl*>::iterator& i)
	{
		AsmCmdOrLbl *p1 = 0, *p2 = 0;
		if (get_2_cmd_or_lbl(body, i, p1, p2)) {
			if (p1->IsCmd(ASM_SUB) && p2->IsCmd(ASM_ADD) &&
				are_operands_equal(
					static_cast<AsmCmd_2*>(p1)->op1,
					static_cast<AsmCmd_2*>(p2)->op1) &&
				are_operands_equal(
					static_cast<AsmCmd_2*>(p1)->op2,
					static_cast<AsmCmd_2*>(p2)->op2))
			{
				erase_2_cmd_or_lbl(body, i);
				return true;
			}
		}
		return false;
	}

}

void AsmProc::Optimize()
{
	const int OPT_NUMBER = 7;
	bool (*opt[OPT_NUMBER])(ListP<AsmCmdOrLbl*>&,
		ListP<AsmCmdOrLbl*>::iterator&) =
	{
		&opt1, &opt2, &opt3, &opt4, &opt5, &opt6, &opt7
	};

	bool flag = true;
	while (flag) {
		flag = false;
		ListP<AsmCmdOrLbl*>::iterator i = body.begin();
		while (1) {
			for (int j = 0; j < OPT_NUMBER; ++j) {
				if (i == body.end())
					break;
				flag = flag || (*opt[j])(body, i);
			}
			if (i == body.end())
				break;
			++i;
		}
	}
}

void AsmProgram::Optimize()
{
	for (ListP<AsmProc*>::iterator i = proc_list.begin();
		i != proc_list.end(); ++i)
	{
		(*i)->Optimize();
	}
}

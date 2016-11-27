#include "asm_program.h"

void AsmOpIntConst::Output(std::ostream& out)
{
	out << "dword ptr " << value;
}

void AsmOpData::Output(std::ostream& out)
{
	out << name.c_str();
}

void AsmOpOffsetData::Output(std::ostream& out)
{
	out << "offset " << name.c_str();
}

void AsmOpProc::Output(std::ostream& out)
{
	out << PREFIX_FUNC.c_str() << name.c_str();
}

void AsmOpLbl::Output(std::ostream& out)
{
	out << PREFIX_LABEL.c_str() << num;
}

void AsmOpReg::Output(std::ostream& out)
{
	out << ASM_REGS_STR[reg];
}

void AsmOpRegOffset::Output(std::ostream& out)
{
	out << "dword ptr " << (seg == ASM_SEG_DS ? "" : "ss:") <<
		'[' << ASM_REGS_STR[reg] << ']';
}

void AsmOpWordZero::Output(std::ostream& out)
{
	out << 0;
}

void AsmLbl::Output(std::ostream& out)
{
	out << PREFIX_LABEL.c_str() << num << ':';
}

void AsmCmd::OutputOpcode(std::ostream& out)
{
	out << '\t' << ASM_OPCODES_STR[opcode];
}

void AsmCmd_0::Output(std::ostream& out)
{
	OutputOpcode(out);
}

void AsmCmd_1::Output(std::ostream& out)
{
	OutputOpcode(out);
	out << '\t';
	op->Output(out);
}

void AsmCmd_2::Output(std::ostream& out)
{
	OutputOpcode(out);
	out << '\t';
	op1->Output(out);
	out << ',';
	op2->Output(out);
}

void AsmProc::Output(std::ostream& out)
{
	out << '\n';
	out << PREFIX_FUNC.c_str() << name.c_str() << " proc";
	out << '\n';
	int params_size = 4*params.size();
	int locals_size = 0;
	for (Locals::iterator i = locals.begin(); i != locals.end(); ++i)
		locals_size += 4*i->size;
	out << '\t' << PREFIX_RESULT.c_str();
	out << '\t' << "equ dword ptr ";
	int k = EBP_SIZE + locals_size + RETURN_ADDRESS_SIZE + params_size;
	out << "ss:[ebp+" << k << "]";
	out << '\n';
	for (Params::iterator i = params.begin(); i != params.end(); ++i) {		
		k -= 4;
		out << '\t' << PREFIX_PARAMETER.c_str() << i->c_str();
		out << '\t' << "equ dword ptr ";
		out << "ss:[ebp+" << k << "]";
		out << '\n';
	}
	k -= RETURN_ADDRESS_SIZE;
	for (Locals::iterator i = locals.begin(); i != locals.end(); ++i) {
		k -= 4*i->size;
		out << '\t' << PREFIX_LOCAL_VAR.c_str() << i->name.c_str();
		out << '\t' << "equ dword ptr ";
		out << "ss:[ebp+" << k << "]";
		out << '\n';
	}
	out << '\t' << "sub\tesp," << locals_size << '\n';
	out << '\t' << "push\tebp" << '\n';
	out << '\t' << "mov\tebp,esp" << '\n';
	out << '\n';

	for (ListP<AsmCmdOrLbl*>::iterator i = body.begin();
		i != body.end(); ++i)
	{
		(*i)->Output(out);
		out << '\n';
	}

	out << '\n';
	out << PREFIX_EXIT.c_str() << ':' << '\n';
	out << '\t' << "pop\tebp" << '\n';
	out << '\t' << "add\tesp," << locals_size << '\n';
	out << '\t' << "ret\t" << params_size;
	out << '\n';
	out << PREFIX_FUNC.c_str() << name.c_str() << " endp";
	out << '\n';
}

void AsmDataSegment::Output(std::ostream& out)
{
	for (std::vector<std::pair<std::string, int> >::iterator i =
		dd_dup_dirs.begin(); i != dd_dup_dirs.end(); ++i)
	{
		out << '\t';
		out << i->first.c_str();
		out << '\t';
		out << "dd";
		out << '\t';
		out << i->second << " dup (0)";
		out << '\n';
	}
	int k = 1;
	for (std::vector<double>::iterator i = dd_float_dirs.begin();
		i != dd_float_dirs.end(); ++i, ++k)
	{
		out << '\t';
		out << PREFIX_REAL_CONST.c_str() << k;
		out << '\t';
		out << "dd";
		out << '\t';
		out << *i;
		out << '\n';
	}
	k = 1;
	for (std::vector<std::string>::iterator i = db_string_dirs.begin();
		i != db_string_dirs.end(); ++i, ++k)
	{
		out << '\t';
		out << PREFIX_STRING_CONST.c_str() << k;
		out << '\t';
		out << "db ";
		out << '\t';
		bool flag = false;
		for (int j = 0; j < i->size(); ++j) {
			int d = (int)((*i)[j]);
			char buf[50];
			std::string s = _itoa(d, buf, 16);
			if (flag)
				out << ", ";			
			flag = true;
			out << '0' << s.c_str() << 'h';
		}
		out << ", \"$\"";
		out << '\n';
	}
}

void AsmProgram::Output(std::ostream& out)
{
	std::ios_base::fmtflags old_flags = out.flags();
	out.setf(std::ios_base::scientific);
	out << "include a1.inc" << "\n\n";
	data_segment.Output(out);
	out << "\ninclude a2.inc" << '\n';
	for (ListP<AsmProc*>::iterator i = proc_list.begin();
		i != proc_list.end(); ++i)
	{
		(*i)->Output(out);
	}
	out << "\ninclude b.inc";
	out.flags(old_flags);
}

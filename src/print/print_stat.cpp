#include "..\parser\stat.h"

#include "print_inc.h"

void ExpStat::Print(int indent_level, std::ostream& out) const
{
	if (exp.get())
		exp->Print(indent_level, out);
	PrintString(";", indent_level, out);
}

void CompoundStat::Print(int indent_level, std::ostream& out) const
{
	PrintString("{", indent_level, out);
	sym_table.Print(indent_level+1, out);
	out << '\n';
	for (StatList::const_iterator i = stat_list.begin();
		i != stat_list.end(); ++i)
	{
		(*i)->Print(indent_level+1, out);
	}
	PrintString("}", indent_level, out);
}

void SelectionStat::Print(int indent_level, std::ostream& out) const
{
	PrintString("if (", indent_level, out);
	exp->Print(indent_level+1, out);
	PrintString(")", indent_level, out);
	stat1->Print(indent_level+1, out);
	if (stat2.get()) {
		PrintString("else", indent_level, out);
		stat2->Print(indent_level+1, out);
	}
}

void IterationStatWhile::Print(int indent_level, std::ostream& out) const
{
	PrintString("while (", indent_level, out);
	exp->Print(indent_level+1, out);
	PrintString(")", indent_level, out);
	stat->Print(indent_level+1, out);
}

void IterationStatDoWhile::Print(int indent_level, std::ostream& out) const
{
	PrintString("do", indent_level, out);
	stat->Print(indent_level+1, out);
	PrintString("while (", indent_level, out);
	exp->Print(indent_level+1, out);
	PrintString(");", indent_level, out);
}

void IterationStatFor::Print(int indent_level, std::ostream& out) const
{
	PrintString("for (", indent_level, out);
	if (exp1.get())
		exp1->Print(indent_level+1, out);
	PrintString(";", indent_level, out);
	if (exp2.get())
		exp2->Print(indent_level+1, out);
	PrintString(";", indent_level, out);
	if (exp3.get())
		exp3->Print(indent_level+1, out);
	PrintString(")", indent_level, out);
	stat->Print(indent_level+1, out);
}

void JumpStatContinue::Print(int indent_level, std::ostream& out) const
{
	PrintString("continue;", indent_level, out);
}

void JumpStatBreak::Print(int indent_level, std::ostream& out) const
{
	PrintString("break;", indent_level, out);
}

void JumpStatReturn::Print(int indent_level, std::ostream& out) const
{
	if (!exp.get())
		PrintString("return;", indent_level, out);
	else {
		PrintString("return", indent_level, out);
		exp->Print(indent_level+1, out);
		PrintString(";", indent_level, out);
	}
}

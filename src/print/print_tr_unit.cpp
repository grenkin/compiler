#include "..\parser\tr_unit.h"

#include "print_inc.h"

void FunctionDefinition::Print(int indent_level, std::ostream& out)
{
	PrintSpaces(indent_level, out);
	AbstractDeclaratorElemFunc *p = new AbstractDeclaratorElemFunc(param_list.CreateCopy());
	result_type.abstract_declarator.PushFront(std::auto_ptr<AbstractDeclaratorElem>(p));
	result_type.Print(name, indent_level, out);
	result_type.abstract_declarator.PopFront();
	out << '\n';
	if (compound_stat.get())
		compound_stat->Print(indent_level, out);
}

void TranslationUnit::Print(int indent_level, std::ostream& out) const
{
	global_sym_table.Print(indent_level, out);
	for (MapP<FunctionDefinition*>::const_iterator i = func_def.begin();
		i != func_def.end(); ++i)
	{
		out << '\n';
		i->second->Print(indent_level, out);
	}
}

#include "..\parser\tr_unit.h"

void FunctionDefinition::Generate(AsmProgram& asm_program) const
{
	AsmProc::Params params;
	AsmProc::Locals locals;
	for (ParamList::const_iterator i = param_list.begin();
		i != param_list.end(); ++i)
	{
		params.push_back((*i)->name);
	}
	for (MapP<Decl1*>::const_iterator i = compound_stat->sym_table.scope1.begin();
		i != compound_stat->sym_table.scope1.end(); ++i)
	{
		bool is_param = false;
		for (ParamList::const_iterator j = param_list.begin();
			j != param_list.end(); ++j)
		{
			if ((*j)->name == i->first) {
				is_param = true;
				break;
			}
		}
		if (!is_param) {
			if (i->second->GetDecl1Class() == DECL1_CLASS_VAR)
				locals.push_back(AsmProc::LocalVar(i->first,
					static_cast<DeclVar*>(i->second)->type.GetSize()));
		}
	}
	asm_program.NewProc(name, result_type.IsVoid(), params, locals);
	compound_stat->Generate(true, asm_program);
}

void TranslationUnit::Generate(AsmProgram& asm_program) const
{
	for (MapP<Decl1*>::const_iterator i = global_sym_table.scope1.begin();
		i != global_sym_table.scope1.end(); ++i)
	{
		if (i->second->GetDecl1Class() == DECL1_CLASS_VAR)
			asm_program.DirDdDup(
				PREFIX_GLOBAL_VAR + i->first,
				static_cast<DeclVar*>(i->second)->type.GetSize());
	}
	for (MapP<FunctionDefinition*>::const_iterator i = func_def.begin();
		i != func_def.end(); ++i)
	{
		if (i->first != "print_int" && i->first != "print_float" && i->first != "print_string")
			i->second->Generate(asm_program);
	}
}

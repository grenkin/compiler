#include "tr_unit.h"
#include "..\errors\errors.h"

DeclFunc::DeclFunc(FunctionDefinition* func_def)
	: func_def(func_def)
{
}

FunctionDefinition* GlobalSymTable::InsertDeclFunc(const std::string& id,
	ExprType result_type, ParamList param_list,
	TranslationUnit& translation_unit)
//ѕоиск согласованного объ¤влени¤ функции.
//≈сли объ¤вление не найдено, создаЄтс¤ новое.
{
	MapP<Decl1*>::iterator i = scope1.find(id);
	if (i == scope1.end()) {
		//внешнее объ¤вление с именем id не найдено
		FunctionDefinition* func_def = new FunctionDefinition(id);
		std::auto_ptr<FunctionDefinition> fd(func_def);
		fd->result_type = result_type;
		fd->param_list = param_list;
		DeclFunc* decl_func = new DeclFunc(fd.get());
		scope1.Insert(id, std::auto_ptr<Decl1>(decl_func));
		translation_unit.func_def.Insert(id, fd);
		return func_def;
	}
	else {
		//найдено внешнее объ¤вление с именем id
		if (i->second->GetDecl1Class() != DECL1_CLASS_FUNC)
			throw IdRedeclarationError();
		DeclFunc* decl_func2 = static_cast<DeclFunc*>(i->second);
		//ѕроверка согласованности объ¤влений...
		if (!(result_type == decl_func2->func_def->result_type) ||
			!CompareParamLists(param_list, decl_func2->func_def->param_list))
		{
			throw IdRedeclarationError();
		}
		//≈сли дл¤ найденного объ¤влени¤ нет определени¤, то
		//обновл¤етс¤ param_list
		if (!decl_func2->func_def->compound_stat.get()) {
			ParamList::iterator i = decl_func2->func_def->param_list.begin();
			ParamList::iterator j = param_list.begin();
			for (; j != param_list.end(); ++i, ++j)
				(*i)->name = (*j)->name;
		}
		return decl_func2->func_def;
	}
}

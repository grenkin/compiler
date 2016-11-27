#include "..\parser\exp.h"
#include "..\parser\decl.h"

#include "print_inc.h"

void SymTableBlock::Print(int indent_level, std::ostream& out) const
{
	for (MapP<Decl1*>::const_iterator i = scope1.begin(); i != scope1.end(); ++i)
		i->second->Print(i->first, indent_level, out);
}

void SymTableStruct::Print(int indent_level, std::ostream& out) const
{
	for (MapP<StructDecl*>::const_iterator i = scope.begin(); i != scope.end(); ++i)
		i->second->Print(i->first, indent_level, out);
}

void DeclVar::Print(const std::string& id, int indent_level, std::ostream& out) const
{
	PrintSpaces(indent_level, out);
	if (storage_class == STOR_CL_STATIC) {
		PrintKeyword(IDENT_OR_KEYWORD_STATIC, out);
		out << " ";
	}
	type.Print(id, indent_level, out);
	out << '\n';
}

void DeclTypedefName::Print(const std::string& id, int indent_level,
	std::ostream& out) const
{
	PrintSpaces(indent_level, out);
	PrintKeyword(IDENT_OR_KEYWORD_TYPEDEF, out);
	out << " ";
	type.Print(id, indent_level, out);
	out << '\n';
}

void DeclEnumConst::Print(const std::string& id, int indent_level,
	std::ostream& out) const
{
	PrintSpaces(indent_level, out);
	out << "enum_const " << id << " = " << value << '\n';
}

void DeclTypeStruct::Print(int indent_level, std::ostream& out) const
{
	PrintKeyword(IDENT_OR_KEYWORD_STRUCT, out);
	out << " {" << '\n';
	sym_table.Print(indent_level+1, out);
	PrintSpaces(indent_level, out);
	out << '}';
}

void DeclTypeEnum::Print(int indent_level, std::ostream& out) const
{
	PrintKeyword(IDENT_OR_KEYWORD_ENUM, out);
}

void StructDecl::Print(const std::string& id, int indent_level,
	std::ostream& out) const
{
	PrintSpaces(indent_level, out);
	type.Print(id, indent_level, out);
	out << '\n';
}

void ExprType::Print(const std::string& id, int indent_level,
	std::ostream& out) const
{
	if (type_qualifiers == TYPE_QUAL_CONST) {
		PrintKeyword(IDENT_OR_KEYWORD_CONST, out);
		out << " ";
	}
	type_spec->Print(indent_level, out);
	out << " ";
	PrintDeclarator(abstract_declarator, id, indent_level, out);
}

void BaseTypeSpec::Print(int indent_level, std::ostream& out) const
{
	PrintKeyword(BASE_TYPES_KEYWORDS[base_type], out);
}

void StructSpec::Print(int indent_level, std::ostream& out) const
{
	decl_type_struct->Print(indent_level, out);
}

void EnumSpec::Print(int indent_level, std::ostream& out) const
{
	decl_type_enum->Print(indent_level, out);
}

void AbstractDeclaratorElemPointer::Print(int indent_level,
	std::ostream& out) const
{
	out << '*';
	if (type_qualifiers == TYPE_QUAL_CONST) {
		PrintKeyword(IDENT_OR_KEYWORD_CONST, out);
		out << ' ';
	}
}

void AbstractDeclaratorElemArray::Print(int indent_level,
	std::ostream& out) const
{
	out << '[';
	if (const_exp_value != 0)
		out << const_exp_value;
	out << ']';
}

void ParamDecl::Print(int indent_level, std::ostream& out) const
{
	type.Print(name, indent_level, out);
}

void AbstractDeclaratorElemFunc::Print(int indent_level, std::ostream& out) const
{
	out << '(';
	PrintParamList(param_list, indent_level, out);
	out << ')';
}

void PrintParamList(const ParamList& param_list, int indent_level, std::ostream& out)
{
	bool flag = false;
	for (ParamList::const_iterator i = param_list.begin();
		i != param_list.end(); ++i)
	{
		if (flag)
			out << ", ";
		ParamDecl* p = *i;
		p->Print(indent_level, out);
		flag = true;
	}
}

void PrintDeclarator(const AbstractDeclarator& abstr_decl,
	const std::string& id, int indent_level, std::ostream& out)
{
	/*
	l -- то, что слева от идентификатора,
	r -- то, что справа от идентификатора.
	Нулевой указатель означает '(' или ')'.
	*/
	std::vector<AbstractDeclaratorElem*> l, r;
	bool was_pointer = false;
	for (AbstractDeclarator::const_iterator i = abstr_decl.begin();
		i != abstr_decl.end(); ++i)
	{
		if ((*i)->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_POINTER)
		{
			l.push_back(*i);
			was_pointer = true;
		}
		else {
			if (was_pointer) {
				l.push_back(0);
				r.push_back(0);
			}
			r.push_back(*i);
			was_pointer = false;
		}
	}
	for (std::vector<AbstractDeclaratorElem*>::reverse_iterator i = l.rbegin();
		i != l.rend(); ++i)
	{
		if (!(*i))
			out << '(';
		else
			(*i)->Print(indent_level, out);
	}
	out << id;
	for (std::vector<AbstractDeclaratorElem*>::iterator i = r.begin();
		i != r.end(); ++i)
	{
		if (!(*i))
			out << ')';
		else
			(*i)->Print(indent_level, out);
	}
}

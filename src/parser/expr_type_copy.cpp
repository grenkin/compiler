#include "exp.h"

ExprType ExprType::CreateCopy() const
{
	ExprType expr_type;
	expr_type.type_spec = type_spec->CreateCopy();
	expr_type.type_qualifiers = type_qualifiers;
	expr_type.abstract_declarator = abstract_declarator.CreateCopy();
	return expr_type;
}

std::auto_ptr<TypeSpec> BaseTypeSpec::CreateCopy() const
{
	BaseTypeSpec* p = new BaseTypeSpec(base_type);
	return std::auto_ptr<TypeSpec>(p);
}

std::auto_ptr<TypeSpec> StructSpec::CreateCopy() const
{
	StructSpec* p = new StructSpec(decl_type_struct);
	return std::auto_ptr<TypeSpec>(p);
}

std::auto_ptr<TypeSpec> EnumSpec::CreateCopy() const
{
	EnumSpec* p = new EnumSpec(decl_type_enum);
	return std::auto_ptr<TypeSpec>(p);
}

std::auto_ptr<AbstractDeclaratorElem> AbstractDeclaratorElemPointer::CreateCopy() const
{
	AbstractDeclaratorElemPointer* p = new AbstractDeclaratorElemPointer(type_qualifiers);
	return std::auto_ptr<AbstractDeclaratorElem>(p);
}

std::auto_ptr<AbstractDeclaratorElem> AbstractDeclaratorElemArray::CreateCopy() const
{
	AbstractDeclaratorElemArray* p = new AbstractDeclaratorElemArray(const_exp_value);
	return std::auto_ptr<AbstractDeclaratorElem>(p);
}

std::auto_ptr<ParamDecl> ParamDecl::CreateCopy() const
{
	ParamDecl* p = new ParamDecl(type.CreateCopy(), name);
	return std::auto_ptr<ParamDecl>(p);
}

std::auto_ptr<AbstractDeclaratorElem> AbstractDeclaratorElemFunc::CreateCopy() const
{
	AbstractDeclaratorElemFunc* p =
		new AbstractDeclaratorElemFunc(param_list.CreateCopy());
	return std::auto_ptr<AbstractDeclaratorElem>(p);
}

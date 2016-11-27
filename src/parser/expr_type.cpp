#include "decl.h"

ExprType::ExprType()
	: type_qualifiers(TYPE_QUAL_NONE)
{
}

void ExprType::AddAbstractDeclarator(AbstractDeclarator& abstr_decl)
{
	AddDeclaratorSuffix(abstract_declarator, abstr_decl);
}

bool ExprType::CheckAbstractDeclaratorCorrectness() const
/* Условия корректности
	1) '[' const_exp ']': константное выражение должно быть целочисленным и
	   больше 0 (см. Parser::ParseDeclaratorSuffix()).
	2) Тип, из которого создаётся массив, должен быть полным.
	3) Нельзя создать массив функций.
	4) Нельзя создать массив из элементов типа void.
	5) Тип возвращаемого значения функции должен быть полным.
	6) Тип возвращаемого значения функции не может быть "массив" или "функция".
*/
{
	if (abstract_declarator.empty())
		return true;
	// 1)
	for (AbstractDeclarator::const_iterator k = abstract_declarator.begin();
		k != abstract_declarator.end(); ++k)
	{
		if ((*k)->GetAbstractDeclaratorElemClass() == ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY) {
			if (static_cast<AbstractDeclaratorElemArray*>(*k)->
				const_exp_value < 0)
			{
				return false;
			}
		}
	}
	AbstractDeclarator::const_iterator i = abstract_declarator.begin(),
		j = abstract_declarator.begin();
	++j;
	for (; j != abstract_declarator.end(); ++i, ++j)
	{
		AbstractDeclaratorElemClass class1 =
			(*i)->GetAbstractDeclaratorElemClass();
		AbstractDeclaratorElemClass class2 =
			(*j)->GetAbstractDeclaratorElemClass();
		if (class1 == ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY) {
			if (class2 == ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY) {
				if (static_cast<AbstractDeclaratorElemArray*>(*j)->
					const_exp_value == 0) // 2)
				{
					return false;
				}
			}
			else if (class2 == ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC) // 3)
				return false;
		}
		else if (class1 == ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC) {
			if (class2 == ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY ||
				class2 == ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC) // 6)
			{
				return false;
			}
		}
	}
	if (abstract_declarator.back()->GetAbstractDeclaratorElemClass() ==
		ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY)
	{
		if (Incomplete()) // 2)
			return false;
		if (IsVoid()) // 4)
			return false;
	}
	else if (abstract_declarator.back()->GetAbstractDeclaratorElemClass() ==
		ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC)
	{
		if (Incomplete()) // 5)
			return false;
	}
	return true;
}

int ExprType::GetSize() const
{
	int k = 1;
	for (AbstractDeclarator::const_iterator i = abstract_declarator.begin();
		i != abstract_declarator.end(); ++i)
	{
		if ((*i)->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_POINTER)
		{
			return k;
		}
		else if ((*i)->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY)
		{
			k *= static_cast<AbstractDeclaratorElemArray*>(*i)->const_exp_value;
		}
	}
	if (type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_STRUCT)
		return k * static_cast<StructSpec*>(type_spec.get())->
			decl_type_struct->struct_size;
	else
		return k;
}

bool ExprType::operator==(const ExprType& expr_type2) const
{
	ExprType a = this->CreateCopy();
	a.abstract_declarator.clear();
	ExprType b = expr_type2.CreateCopy();
	b.abstract_declarator.clear();
	if (a.IsStruct() || b.IsStruct()) {
		if (!a.IsStruct() || !b.IsStruct())
			return false;
		if (!(
			static_cast<StructSpec*>(a.type_spec.get())->decl_type_struct ==
			static_cast<StructSpec*>(b.type_spec.get())->decl_type_struct))
		{
			return false;
		}
	}
	if (a.IsVoid() || b.IsVoid())
		return false;
	if (a.IsIntegral() && !b.IsIntegral() || !a.IsIntegral() && b.IsIntegral())
		return false;
	if (this->abstract_declarator.size() != expr_type2.abstract_declarator.size())
		return false;
	AbstractDeclarator::const_iterator i = this->abstract_declarator.begin(),
		j = expr_type2.abstract_declarator.begin();
	for (; i != this->abstract_declarator.end(); ++i, ++j) {
		if ((*i)->GetAbstractDeclaratorElemClass() !=
			(*j)->GetAbstractDeclaratorElemClass())
		{
			return false;
		}
		if ((*i)->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC)
		{
			AbstractDeclaratorElemFunc* p1 = static_cast<AbstractDeclaratorElemFunc*>(*i);
			AbstractDeclaratorElemFunc* p2 = static_cast<AbstractDeclaratorElemFunc*>(*j);
			if (!CompareParamLists(p1->param_list, p2->param_list))
				return false;
		}
	}
	return true;
}

bool ExprType::Incomplete() const
{
	return (abstract_declarator.empty() &&
		type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_STRUCT &&
		static_cast<StructSpec*>(type_spec.get())->decl_type_struct->incomplete ||
		!abstract_declarator.empty() &&
		abstract_declarator.front()->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY &&
		static_cast<AbstractDeclaratorElemArray*>(
			abstract_declarator.front())->const_exp_value == 0);
}

bool ExprType::IsVoid() const
{
	if (type_qualifiers != TYPE_QUAL_NONE)
		return false;
	if (!abstract_declarator.empty())
		return false;
	return (type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_BASE &&
		static_cast<BaseTypeSpec*>(type_spec.get())->base_type ==
		BASE_TYPE_VOID);
}

bool ExprType::IsPointer() const
{
	return (!abstract_declarator.empty() &&
		abstract_declarator.front()->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_POINTER);
}

bool ExprType::IsArray() const
{
	return (!abstract_declarator.empty() &&
		abstract_declarator.front()->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY);
}

bool ExprType::IsFunc() const
{
	return (!abstract_declarator.empty() &&
		abstract_declarator.front()->GetAbstractDeclaratorElemClass() ==
			ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC);
}

bool ExprType::IsIntegral() const
{
	if (!abstract_declarator.empty())
		return false;
	if (type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_STRUCT)
		return false;
	if (type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_ENUM)
		return true;
	//type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_BASE
	BaseTypeT base_type = static_cast<BaseTypeSpec*>(type_spec.get())->base_type;
	return (base_type == BASE_TYPE_INT || base_type == BASE_TYPE_CHAR);
}

bool ExprType::IsFloat() const
{
	return (abstract_declarator.empty() &&
		type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_BASE &&
		static_cast<BaseTypeSpec*>(type_spec.get())->base_type ==
			BASE_TYPE_FLOAT);
}

bool ExprType::IsArithmetic() const
{
	return (IsIntegral() || IsFloat());
}

bool ExprType::IsStruct() const
{
	return (abstract_declarator.empty() &&
		type_spec->GetTypeSpecClass() == TYPE_SPEC_CLASS_STRUCT);
}

ExprType ExprType::GetPointerType() const
//Предполагается, что IsPointer() == true
{
	ExprType expr_type2 = CreateCopy();
	expr_type2.abstract_declarator.PopFront();
	return expr_type2;
}

void ExprType::SetInt()
{
	type_spec = std::auto_ptr<TypeSpec>(new BaseTypeSpec(BASE_TYPE_INT));
}

void ExprType::SetFloat()
{
	type_spec = std::auto_ptr<TypeSpec>(new BaseTypeSpec(BASE_TYPE_FLOAT));
}

void ExprType::SetVoid()
{
	type_spec = std::auto_ptr<TypeSpec>(new BaseTypeSpec(BASE_TYPE_VOID));
}

void ExprType::SetChar()
{
	type_spec = std::auto_ptr<TypeSpec>(new BaseTypeSpec(BASE_TYPE_CHAR));
}

void ExprType::MakePointer()
{
	AbstractDeclaratorElemPointer* p =
		new AbstractDeclaratorElemPointer(TYPE_QUAL_NONE);
	abstract_declarator.PushFront(
		std::auto_ptr<AbstractDeclaratorElem>(p));
}

void ExprType::PointerGeneration()
{
	if (IsArray() || IsFunc()) {
		if (IsArray())
			abstract_declarator.PopFront();
		MakePointer();
	}
}

BaseTypeSpec::BaseTypeSpec(BaseTypeT base_type)
	: base_type(base_type)
{
}

StructSpec::StructSpec(DeclTypeStruct* decl_type_struct)
	: decl_type_struct(decl_type_struct)
{
}

EnumSpec::EnumSpec(DeclTypeEnum* decl_type_enum)
	: decl_type_enum(decl_type_enum)
{
}

AbstractDeclaratorElemPointer::AbstractDeclaratorElemPointer(TypeQualifiers type_qualifiers)
	: type_qualifiers(type_qualifiers)
{
}

AbstractDeclaratorElemArray::AbstractDeclaratorElemArray(int const_exp_value)
	: const_exp_value(const_exp_value)
{
}

ParamDecl::ParamDecl(ExprType& type, const std::string& name)
	: type(type), name(name)
{
}

AbstractDeclaratorElemFunc::AbstractDeclaratorElemFunc(ParamList& param_list)
	: param_list(param_list)
{
}

void AddPointer(AbstractDeclarator& dest, std::vector<TypeQualifiers>& pointer)
{
	for (std::vector<TypeQualifiers>::const_reverse_iterator i = pointer.rbegin();
		i != pointer.rend(); ++i)
	{
		AbstractDeclaratorElemPointer* p = new AbstractDeclaratorElemPointer(*i);
		dest.PushBack(std::auto_ptr<AbstractDeclaratorElem>(p));
	}
}

void AddDeclaratorSuffix(AbstractDeclarator& dest, AbstractDeclarator& source){
	while (!source.empty())
		dest.PushBack(source.PopFront());	
}

bool CompareParamLists(ParamList& param_list1, ParamList& param_list2)
{
	if (param_list1.size() != param_list2.size())
		return false;
	ParamList::iterator k1 = param_list1.begin(),
		k2 = param_list2.begin();
	for (; k1 != param_list1.end(); ++k1, ++k2) {
		if (!((*k1)->type == (*k2)->type))
			return false;
	}
	return true;
}

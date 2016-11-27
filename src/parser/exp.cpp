#include "tr_unit.h"
#include "..\errors\errors.h"

namespace {

	void throw_types_error(std::string message)
	{
		throw TypesError(message, 0, 0);
	}

	void assert_types(bool condition, std::string message)
	{
		if (!condition)
			throw_types_error(message);
	}

}

void ExprNode::PointerGeneration()
//Генерирование указателя
/*
Если выражение или подвыражение имеет тип "массив элементов T", где
T - некоторый тип, то значением этого выражения будет указатель на
первый элемент массива, и тип такого выражения заменяется на тип
"указатель на T". Замена типа не выполняется, если выражение является
операндом одноместной операции &, либо операндом операций ++, --, либо
левым операндом присваивания или операции "точка". Аналогично, выражение
типа "функция, возвращающая T", кроме случая использования в качестве
операнда &, преобразуется в тип "указатель на функцию, возвращающую T".
*/
{
	expr_type.PointerGeneration();
}

Exp::Exp(ListP<ExprNode*>& assignment_exp_list1)
    : assignment_exp_list(assignment_exp_list1)
{
	for (ListP<ExprNode*>::iterator i = assignment_exp_list.begin();
		i != assignment_exp_list.end(); ++i)
	{
		(*i)->PointerGeneration();
	}
	expr_type = assignment_exp_list.back()->expr_type.CreateCopy();
	is_lvalue = false;
	is_const_exp = false;
}

AssignmentExp::AssignmentExp(ExprNodeP unary_exp1, ExprNodeP assignment_exp1)
    : unary_exp(unary_exp1), assignment_exp(assignment_exp1)
{
	assignment_exp->PointerGeneration();
	assert_types(unary_exp->is_lvalue,
		"The first operand must be lvalue");
	assert_types(!unary_exp->expr_type.IsArray() &&
		!unary_exp->expr_type.IsFunc() &&
		!unary_exp->expr_type.Incomplete(),
		"The first operand can\'t be an array or a function or have incomplete type");
	assert_types(unary_exp->expr_type.type_qualifiers != TYPE_QUAL_CONST,
		"The first operand can\'t have const qualifier");
	assert_types(unary_exp->expr_type == assignment_exp->expr_type ||
		unary_exp->expr_type.IsIntegral() && assignment_exp->expr_type.IsFloat() ||
		unary_exp->expr_type.IsFloat() && assignment_exp->expr_type.IsIntegral(),
		"Types of the operands must be equal");
	expr_type = unary_exp->expr_type.CreateCopy();
	is_lvalue = true;
	is_const_exp = false;
}

ConditionalExp::ConditionalExp(ExprNodeP logical_or_exp1, ExprNodeP exp1,
    ExprNodeP conditional_exp1)
    : logical_or_exp(logical_or_exp1), exp(exp1), conditional_exp(conditional_exp1)
{
	logical_or_exp->PointerGeneration();
	exp->PointerGeneration();
	conditional_exp->PointerGeneration();
	assert_types(logical_or_exp->expr_type.IsArithmetic() &&
		exp->expr_type.IsArithmetic() &&
		conditional_exp->expr_type.IsArithmetic(),
		"Types of the expressions must be arithmetic");
	if (exp->expr_type.IsFloat() || conditional_exp->expr_type.IsFloat())
		expr_type.SetFloat();
	else
		expr_type.SetInt();
	is_lvalue = false;
	is_const_exp = logical_or_exp->is_const_exp && exp->is_const_exp &&
		conditional_exp->is_const_exp;
	if (is_const_exp)
		const_exp_value = logical_or_exp->const_exp_value ?
			exp->const_exp_value : conditional_exp->const_exp_value;
}

BinaryExp::BinaryExp(BinaryExpClass binary_exp_class1, ExprNodeP arg11,
    OperatorT op1, ExprNodeP arg21)
    : binary_exp_class(binary_exp_class1), arg1(arg11), op(op1), arg2(arg21)
{
	arg1->PointerGeneration();
	arg2->PointerGeneration();
	switch (op) {
		case OP_VERT_LINE_VERT_LINE:
		case OP_AMP_AMP:
			assert_types(
				(arg1->expr_type.IsArithmetic() || arg1->expr_type.IsPointer()) &&
				(arg2->expr_type.IsArithmetic() || arg2->expr_type.IsPointer()),
				"Each operand must have an arithmetic type or be a pointer");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				if (op == OP_VERT_LINE_VERT_LINE)
					const_exp_value = arg1->const_exp_value || arg2->const_exp_value;
				else
					const_exp_value = arg1->const_exp_value && arg2->const_exp_value;
			}
			break;
		case OP_VERT_LINE:
		case OP_COVER:
		case OP_AMP:
			assert_types(arg1->expr_type.IsIntegral() &&
				arg2->expr_type.IsIntegral(),
				"Types of operands must be integral");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				if (op == OP_VERT_LINE)
					const_exp_value = arg1->const_exp_value | arg2->const_exp_value;
				else if (op == OP_COVER)
					const_exp_value = arg1->const_exp_value ^ arg2->const_exp_value;
				else
					const_exp_value = arg1->const_exp_value & arg2->const_exp_value;
			}
			break;
		case OP_EQUAL_EQUAL:
		case OP_EXCL_MARK_EQUAL:
		case OP_LESS:
		case OP_MORE:
		case OP_LESS_EQUAL:
		case OP_MORE_EQUAL:
			assert_types(arg1->expr_type.IsArithmetic() &&
				arg2->expr_type.IsArithmetic(),
				"Types of operands must be arithmetic");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				if (op == OP_EQUAL_EQUAL)
					const_exp_value = arg1->const_exp_value == arg2->const_exp_value;
				else if (op == OP_EXCL_MARK_EQUAL)
					const_exp_value = arg1->const_exp_value != arg2->const_exp_value;
				else if (op == OP_LESS)
					const_exp_value = arg1->const_exp_value < arg2->const_exp_value;
				else if (op == OP_MORE)
					const_exp_value = arg1->const_exp_value > arg2->const_exp_value;
				else if (op == OP_LESS_EQUAL)
					const_exp_value = arg1->const_exp_value <= arg2->const_exp_value;
				else
					const_exp_value = arg1->const_exp_value >= arg2->const_exp_value;
			}
			break;
		case OP_LESS_LESS:
		case OP_MORE_MORE:
			assert_types(arg1->expr_type.IsIntegral() &&
				arg2->expr_type.IsIntegral(),
				"Types of operands must be integral");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				if (op == OP_LESS_LESS)
					const_exp_value =
						arg1->const_exp_value << arg2->const_exp_value;
				else
					const_exp_value =
						arg1->const_exp_value >> arg2->const_exp_value;
			}
			break;
		case OP_PLUS:
		case OP_MINUS:
			if (arg1->expr_type.IsArithmetic() && arg2->expr_type.IsArithmetic()) {
				if (arg1->expr_type.IsFloat() || arg2->expr_type.IsFloat())
					expr_type.SetFloat();
				else
					expr_type.SetInt();
				is_const_exp = arg1->is_const_exp && arg2->is_const_exp;
				if (is_const_exp) {
					if (op == OP_PLUS)
						const_exp_value = arg1->const_exp_value + arg2->const_exp_value;
					else
						const_exp_value = arg1->const_exp_value - arg2->const_exp_value;
				}
			}
			else if (arg1->expr_type.IsPointer() && arg2->expr_type.IsIntegral()) {
				expr_type = arg1->expr_type.CreateCopy();
				is_const_exp = false;
			}
			else if (arg1->expr_type.IsIntegral() && arg2->expr_type.IsArithmetic()) {
				expr_type = arg2->expr_type.CreateCopy();
				is_const_exp = false;
			}
			else if (op == OP_MINUS && arg1->expr_type.IsPointer() &&
				arg2->expr_type.IsPointer())
			{
				throw_types_error("Difference of pointers");
			}
			else
				throw_types_error("Wrong types of operands");
			is_lvalue = false;
			break;
		case OP_STAR:
		case OP_SLASH:
			assert_types(arg1->expr_type.IsArithmetic() &&
				arg2->expr_type.IsArithmetic(),
				"Types of operands must be arithmetic");
			if (arg1->expr_type.IsFloat() || arg2->expr_type.IsFloat())
				expr_type.SetFloat();
			else
				expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				if (op == OP_STAR)
					const_exp_value =
						arg1->const_exp_value * arg2->const_exp_value;
				else {
					assert_types(arg2->const_exp_value != 0,
						"Division by zero");
					const_exp_value =
						arg1->const_exp_value / arg2->const_exp_value;
				}
			}
			break;
		case OP_PERCENT:
			assert_types(arg1->expr_type.IsIntegral() &&
				arg2->expr_type.IsIntegral(),
				"Types of operands must be integral");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = (arg1->is_const_exp && arg2->is_const_exp);
			if (is_const_exp) {
				assert_types(arg2->const_exp_value != 0,
					"Division by zero");
				const_exp_value = arg1->const_exp_value % arg2->const_exp_value;
			}
			break;
	}
}

UnaryExpIncDec::UnaryExpIncDec(OperatorT inc_dec_operator1, ExprNodeP unary_exp1)
    : inc_dec_operator(inc_dec_operator1), unary_exp(unary_exp1)
{
	assert_types(unary_exp->is_lvalue, "Operand must be lvalue");
	assert_types(unary_exp->expr_type.IsArithmetic() ||
		unary_exp->expr_type.IsPointer(),
		"Operand must have arithmetic type or be a pointer");
	assert_types(unary_exp->expr_type.type_qualifiers == TYPE_QUAL_NONE,
		"Operand must not have const qualifier");
	expr_type = unary_exp->expr_type.CreateCopy();
	is_lvalue = false;
	is_const_exp = false;
}

UnaryExpUnaryOperator::UnaryExpUnaryOperator(OperatorT unary_operator1,
    ExprNodeP unary_exp1)
    : unary_operator(unary_operator1), unary_exp(unary_exp1)
{
	switch (unary_operator) {
		case OP_AMP:
			assert_types(unary_exp->is_lvalue || unary_exp->expr_type.IsFunc(),
				"The operand must be lvalue or an object of type \"function\"");
			expr_type = unary_exp->expr_type.CreateCopy();
			expr_type.MakePointer();
			is_lvalue = false;
			is_const_exp = false;
			break;		
		case OP_STAR:
			unary_exp->PointerGeneration();
			assert_types(unary_exp->expr_type.IsPointer(),
				"The operand must be a pointer");
			expr_type = unary_exp->expr_type.GetPointerType();
			is_lvalue = (expr_type.IsArithmetic() || expr_type.IsStruct() ||
				expr_type.IsPointer());
			is_const_exp = false;
			break;			
		case OP_PLUS:			
		case OP_MINUS:
			unary_exp->PointerGeneration();
			assert_types(unary_exp->expr_type.IsArithmetic(),
				"Type of the operand must be arithmetic");
			expr_type = unary_exp->expr_type.CreateCopy();
			is_lvalue = false;
			is_const_exp = unary_exp->is_const_exp;
			if (is_const_exp)
				const_exp_value = (unary_operator1 == OP_MINUS) ?
					-unary_exp->const_exp_value : unary_exp->const_exp_value;
			break;			
		case OP_SQUIGGLE:
			unary_exp->PointerGeneration();
			assert_types(unary_exp->expr_type.IsIntegral(),
				"Type of the operand must be integral");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = unary_exp->is_const_exp;
			if (is_const_exp)
				const_exp_value = ~unary_exp->const_exp_value;
			break;			
		case OP_EXCL_MARK:
			unary_exp->PointerGeneration();
			assert_types(unary_exp->expr_type.IsArithmetic() ||
				unary_exp->expr_type.IsPointer(),
				"The operand must have arithmetic type or be a pointer");
			expr_type.SetInt();
			is_lvalue = false;
			is_const_exp = unary_exp->is_const_exp;
			if (is_const_exp)
				const_exp_value = !unary_exp->const_exp_value;
			break;
	}
}

PostfixExp::PostfixExp(ExprNodeP postfix_exp1)
    : postfix_exp(postfix_exp1)
{
}

PostfixExpArrayIndex::PostfixExpArrayIndex(ExprNodeP postfix_exp1, ExprNodeP exp1)
    : PostfixExp(postfix_exp1), exp(exp1)
{
	postfix_exp->PointerGeneration();
	exp->PointerGeneration();
	if (postfix_exp->expr_type.IsPointer()) {
		assert_types(exp->expr_type.IsIntegral(),
			"One of operands must be integral");
		expr_type = postfix_exp->expr_type.GetPointerType();
	}
	else if (exp->expr_type.IsPointer()) {
		assert_types(postfix_exp->expr_type.IsIntegral(),
			"One of operands must be integral");
		expr_type = exp->expr_type.GetPointerType();
	}
	else
		throw_types_error("One of operands must be a pointer");
	is_lvalue = (expr_type.IsArithmetic() || expr_type.IsStruct() ||
		expr_type.IsPointer());
	is_const_exp = false;
}

PostfixExpFuncCall::PostfixExpFuncCall(ExprNodeP postfix_exp1,
    ArgumentExpList& argument_exp_list1)
    : PostfixExp(postfix_exp1), argument_exp_list(argument_exp_list1)
{
	postfix_exp->PointerGeneration();
	for (ArgumentExpList::iterator i = argument_exp_list.begin();
		i != argument_exp_list.end(); ++i)
	{
		(*i)->PointerGeneration();
	}
	assert_types(postfix_exp->expr_type.IsPointer(),
		"The first expression must be a pointer to function");
	expr_type = postfix_exp->expr_type.GetPointerType();
	assert_types(expr_type.IsFunc(),
		"The first expression must be a pointer to function");
	std::auto_ptr<AbstractDeclaratorElem> p =
		expr_type.abstract_declarator.PopFront();
	//expr_type -- тип возвращаемого значения функции
	ParamList param_list =
		static_cast<AbstractDeclaratorElemFunc*>(p.get())->param_list;
	assert_types(param_list.size() == argument_exp_list.size(),
		"The numbers of arguments and parameters differ");
	ParamList::iterator i = param_list.begin();
	ArgumentExpList::iterator j = argument_exp_list.begin();
	for (; i != param_list.end(); ++i, ++j)
		assert_types((*i)->type == (*j)->expr_type ||
			(*i)->type.IsIntegral() && (*j)->expr_type.IsFloat() ||
			(*i)->type.IsFloat() && (*j)->expr_type.IsIntegral(),
			"The types of a parameter and an argument differ");
	is_lvalue = false;
	is_const_exp = false;
}

PostfixExpPoint::PostfixExpPoint(ExprNodeP postfix_exp1, std::string id_text)
    : PostfixExp(postfix_exp1), name(id_text)
{
	ExprType* p = 0;
	ExprType expr_type2;
	assert_types(postfix_exp->expr_type.IsStruct(),
		"The first operand must be a structure");
	DeclTypeStruct* decl_type_struct = static_cast<StructSpec*>(
		postfix_exp->expr_type.type_spec.get())->decl_type_struct;
	struct_decl = decl_type_struct->sym_table.FindStructDecl(id_text);
	assert_types(struct_decl, std::string("The field \'")+id_text+
		std::string("\' doesn\'t exist"));
	expr_type = struct_decl->type.CreateCopy();
	is_lvalue = !expr_type.IsArray();
	is_const_exp = false;
}

PostfixExpIncDec::PostfixExpIncDec(ExprNodeP postfix_exp1,
    OperatorT inc_dec_operator1)
    : PostfixExp(postfix_exp1), inc_dec_operator(inc_dec_operator1)
{
	assert_types(postfix_exp->is_lvalue, "Operand must be lvalue");
	assert_types(postfix_exp->expr_type.IsArithmetic() ||
		postfix_exp->expr_type.IsPointer(),
		"Operand must have arithmetic type or be a pointer");
	assert_types(postfix_exp->expr_type.type_qualifiers == TYPE_QUAL_NONE,
		"Operand must not have const qualifier");
	expr_type = postfix_exp->expr_type.CreateCopy();
	is_lvalue = false;
	is_const_exp = false;
}

PrimaryExpVar::PrimaryExpVar(DeclVar* decl_var1, const std::string& name1)
	: decl_var(decl_var1), name(name1)
{
	expr_type = decl_var->type.CreateCopy();
	is_lvalue = true;
	is_const_exp = false;
}

PrimaryExpFunc::PrimaryExpFunc(DeclFunc* decl_func1, const std::string& name1)
	: decl_func(decl_func1), name(name1)
{
	expr_type = decl_func->func_def->result_type.CreateCopy();
	AbstractDeclaratorElemFunc* p = new AbstractDeclaratorElemFunc(
		decl_func->func_def->param_list.CreateCopy());
	expr_type.abstract_declarator.PushFront(std::auto_ptr<AbstractDeclaratorElem>(p));
	is_lvalue = false;
	is_const_exp = false;
}

PrimaryExpIntConst::PrimaryExpIntConst(int const_value1)
    : const_value(const_value1)
{
	expr_type.SetInt();
	is_lvalue = false;
	is_const_exp = true;
	const_exp_value = const_value;
}

PrimaryExpRealConst::PrimaryExpRealConst(double const_value1)
    : const_value(const_value1)
{
	expr_type.SetFloat();
	is_lvalue = false;
	is_const_exp = false;
}

PrimaryExpStringConst::PrimaryExpStringConst(std::string const_value1)
    : const_value(const_value1)
{
	expr_type.type_spec = std::auto_ptr<TypeSpec>(new BaseTypeSpec(BASE_TYPE_CHAR));
	AbstractDeclaratorElemPointer* p = new AbstractDeclaratorElemPointer(TYPE_QUAL_NONE);
	expr_type.abstract_declarator.PushBack(std::auto_ptr<AbstractDeclaratorElem>(p));
	is_lvalue = false;
	is_const_exp = false;
}

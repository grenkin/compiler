#include "exp.h"

ExprNodeP Exp::CreateCopy() const
{
	return ExprNodeP(new Exp(assignment_exp_list.CreateCopy()));
}

ExprNodeP AssignmentExp::CreateCopy() const
{
	return ExprNodeP(new AssignmentExp(
		unary_exp->CreateCopy(),
		assignment_exp->CreateCopy()));
}

ExprNodeP ConditionalExp::CreateCopy() const
{
	return ExprNodeP(new ConditionalExp(
		logical_or_exp->CreateCopy(),
		exp->CreateCopy(),
		conditional_exp->CreateCopy()));
}

ExprNodeP BinaryExp::CreateCopy() const
{
	return ExprNodeP(new BinaryExp(
		binary_exp_class,
		ExprNodeP(arg1->CreateCopy()),
		op,
		ExprNodeP(arg2->CreateCopy())));
}

ExprNodeP UnaryExpIncDec::CreateCopy() const
{
	return ExprNodeP(new UnaryExpIncDec(
		inc_dec_operator,
		unary_exp->CreateCopy()));
}

ExprNodeP UnaryExpUnaryOperator::CreateCopy() const
{
	return ExprNodeP(new UnaryExpUnaryOperator(
		unary_operator,
		unary_exp->CreateCopy()));
}

ExprNodeP PostfixExpArrayIndex::CreateCopy() const
{
	return ExprNodeP(new PostfixExpArrayIndex(
		postfix_exp->CreateCopy(),
		exp->CreateCopy()));
}

ExprNodeP PostfixExpFuncCall::CreateCopy() const
{
	return ExprNodeP(new PostfixExpFuncCall(
		postfix_exp->CreateCopy(),
		argument_exp_list.CreateCopy()));
}

ExprNodeP PostfixExpPoint::CreateCopy() const
{
	return ExprNodeP(new PostfixExpPoint(
		postfix_exp->CreateCopy(), name));
}

ExprNodeP PostfixExpIncDec::CreateCopy() const
{
	return ExprNodeP(new PostfixExpIncDec(
		postfix_exp->CreateCopy(),
		inc_dec_operator));
}

ExprNodeP PrimaryExpVar::CreateCopy() const
{
	return ExprNodeP(new PrimaryExpVar(decl_var, name));
}

ExprNodeP PrimaryExpFunc::CreateCopy() const
{
	return ExprNodeP(new PrimaryExpFunc(decl_func, name));
}

ExprNodeP PrimaryExpIntConst::CreateCopy() const
{
	return ExprNodeP(new PrimaryExpIntConst(const_value));
}

ExprNodeP PrimaryExpRealConst::CreateCopy() const
{
	return ExprNodeP(new PrimaryExpRealConst(const_value));
}

ExprNodeP PrimaryExpStringConst::CreateCopy() const
{
	return ExprNodeP(new PrimaryExpStringConst(const_value));
}

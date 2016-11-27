#include "..\parser\exp.h"

#include "print_inc.h"

void Exp::Print(int indent_level, std::ostream& out) const
{
    bool flag = false;
    for (ListP<ExprNode*>::const_iterator i = assignment_exp_list.begin();
		i != assignment_exp_list.end(); ++i)
	{
        if (flag)
            PrintOperator(OP_COMMA, indent_level, out);
        flag = true;
        (*i)->Print(indent_level+1, out);
    }
}

void AssignmentExp::Print(int indent_level, std::ostream& out) const
{
    unary_exp->Print(indent_level+1, out);
    PrintOperator(OP_EQUAL, indent_level, out);
    assignment_exp->Print(indent_level+1, out);
}

void ConditionalExp::Print(int indent_level, std::ostream& out) const
{
    logical_or_exp->Print(indent_level+1, out);
    PrintOperator(OP_QUEST_MARK, indent_level, out);
    exp->Print(indent_level+1, out);
    PrintOperator(OP_COLON, indent_level, out);
    conditional_exp->Print(indent_level+1, out);
}

void BinaryExp::Print(int indent_level, std::ostream& out) const
{
    arg1->Print(indent_level+1, out);
    PrintOperator(op, indent_level, out);
    arg2->Print(indent_level+1, out);
}

void UnaryExpIncDec::Print(int indent_level, std::ostream& out) const
{
    PrintOperator(inc_dec_operator, indent_level, out);
    unary_exp->Print(indent_level+1, out);
}

void UnaryExpUnaryOperator::Print(int indent_level, std::ostream& out) const
{
    PrintOperator(unary_operator, indent_level, out);
    unary_exp->Print(indent_level+1, out);
}

void PostfixExpArrayIndex::Print(int indent_level, std::ostream& out) const
{
    postfix_exp->Print(indent_level+1, out);
    PrintDelimiter(DELIM_LEFT_SQUARE_BRACKET, indent_level, out);
    exp->Print(indent_level+1, out);
    PrintDelimiter(DELIM_RIGHT_SQUARE_BRACKET, indent_level, out);
}

void PostfixExpFuncCall::Print(int indent_level, std::ostream& out) const
{
    postfix_exp->Print(indent_level+1, out);
    PrintDelimiter(DELIM_LEFT_ROUND_BRACKET, indent_level, out);
	bool flag = false;
	for (ArgumentExpList::const_iterator i = argument_exp_list.begin();
		i != argument_exp_list.end(); ++i)
	{
		if (flag)
			PrintString(",", indent_level, out);
		flag = true;
		(*i)->Print(indent_level+1, out);
	}
    PrintDelimiter(DELIM_RIGHT_ROUND_BRACKET, indent_level, out);
}

void PostfixExpPoint::Print(int indent_level, std::ostream& out) const
{
    postfix_exp->Print(indent_level+1, out);
    PrintOperator(OP_POINT, indent_level, out);
    PrintString(name, indent_level+1, out);
}

void PostfixExpIncDec::Print(int indent_level, std::ostream& out) const
{
    postfix_exp->Print(indent_level+1, out);
    PrintOperator(inc_dec_operator, indent_level, out);
}

void PrimaryExpVar::Print(int indent_level, std::ostream& out) const
{
    PrintString(name, indent_level, out);
}

void PrimaryExpFunc::Print(int indent_level, std::ostream& out) const
{
    PrintString(name, indent_level, out);
}

void PrimaryExpIntConst::Print(int indent_level, std::ostream& out) const
{
    PrintSpaces(indent_level, out);
    out << const_value << '\n';
}

void PrimaryExpRealConst::Print(int indent_level, std::ostream& out) const
{
    PrintSpaces(indent_level, out);
    out << const_value << '\n';
}

void PrimaryExpStringConst::Print(int indent_level, std::ostream& out) const
{
    PrintSpaces(indent_level, out);
    out << const_value << '\n';
}

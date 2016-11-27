#include "parser.h"

namespace {

    bool is_assignment_operator(Token* token, BinaryExpClass& binary_exp_class,
		OperatorT& binary_operator)
    {
        const int ASSIGNMENT_OPERATORS_NUMBER = 11;
        const OperatorT ASSIGNMENT_OPERATORS[ASSIGNMENT_OPERATORS_NUMBER] = {
            OP_EQUAL, OP_STAR_EQUAL, OP_SLASH_EQUAL, OP_PERCENT_EQUAL,
            OP_PLUS_EQUAL, OP_MINUS_EQUAL, OP_LESS_LESS_EQUAL,
            OP_MORE_MORE_EQUAL, OP_AMP_EQUAL, OP_COVER_EQUAL,
            OP_VERT_LINE_EQUAL};
		const BinaryExpClass BINARY_EXP_CLASSES[ASSIGNMENT_OPERATORS_NUMBER] = {
			BINARY_EXP_CLASS_NONE, BINARY_EXP_CLASS_MULT,
			BINARY_EXP_CLASS_MULT, BINARY_EXP_CLASS_MULT,
			BINARY_EXP_CLASS_ADDITIVE, BINARY_EXP_CLASS_ADDITIVE,
			BINARY_EXP_CLASS_SHIFT, BINARY_EXP_CLASS_SHIFT,
			BINARY_EXP_CLASS_AND, BINARY_EXP_CLASS_EXCLUSIVE_OR,
			BINARY_EXP_CLASS_INCLUSIVE_OR};
		const OperatorT BINARY_OPERATORS[ASSIGNMENT_OPERATORS_NUMBER] = {
			OP_NONE, OP_STAR, OP_SLASH, OP_PERCENT, OP_PLUS, OP_MINUS,
			OP_LESS_LESS, OP_MORE_MORE, OP_AMP, OP_COVER, OP_VERT_LINE};
        for (int i = 0; i < ASSIGNMENT_OPERATORS_NUMBER; ++i) {
			if (token->IsOperator(ASSIGNMENT_OPERATORS[i])) {
				binary_exp_class = BINARY_EXP_CLASSES[i];
				binary_operator = BINARY_OPERATORS[i];
                return true;
			}
        }
        return false;
    }

    bool is_binary_operator(BinaryExpClass binary_exp_class, Token* token)
    {
        const int BINARY_EXP_CLASSES_NUMBER = 10;
        const OperatorT BINARY_OPERATORS[BINARY_EXP_CLASSES_NUMBER][4] = {
            {OP_VERT_LINE_VERT_LINE, OP_NONE, OP_NONE, OP_NONE},
            {OP_AMP_AMP, OP_NONE, OP_NONE, OP_NONE},
            {OP_VERT_LINE, OP_NONE, OP_NONE, OP_NONE},
            {OP_COVER, OP_NONE, OP_NONE, OP_NONE},
            {OP_AMP, OP_NONE, OP_NONE, OP_NONE},
            {OP_EQUAL_EQUAL, OP_EXCL_MARK_EQUAL, OP_NONE, OP_NONE},
            {OP_LESS, OP_MORE, OP_LESS_EQUAL, OP_MORE_EQUAL},
            {OP_LESS_LESS, OP_MORE_MORE, OP_NONE, OP_NONE},
            {OP_PLUS, OP_MINUS, OP_NONE, OP_NONE},
            {OP_STAR, OP_SLASH, OP_PERCENT, OP_NONE}};
        for (int i = 0; i < 4 && BINARY_OPERATORS[binary_exp_class][i] !=
            OP_NONE; ++i)
        {
            if (token->IsOperator(BINARY_OPERATORS[binary_exp_class][i]))
                return true;
        }
        return false;
    }

    bool is_unary_operator(Token* token)
    {
        const int UNARY_OPERATORS_NUMBER = 6;
        const OperatorT UNARY_OPERATORS[UNARY_OPERATORS_NUMBER] = {
            OP_AMP, OP_STAR, OP_PLUS, OP_MINUS, OP_SQUIGGLE, OP_EXCL_MARK};
        for (int i = 0; i < UNARY_OPERATORS_NUMBER; ++i) {
            if (token->IsOperator(UNARY_OPERATORS[i]))
                return true;
        }
        return false;
    }

}

void Parser::ThrowSyntaxError(std::string msg)
{
    throw SyntaxError(msg, lexer.GetToken()->Line(), lexer.GetToken()->Pos());
}

void Parser::ThrowTypesError(std::string msg)
{
    throw TypesError(msg, lexer.GetToken()->Line(), lexer.GetToken()->Pos());
}

void Parser::RequireDelimiter(DelimiterT delim, const char* msg)
{
	if (!lexer.GetToken()->IsDelimiter(delim))
		ThrowSyntaxError(msg);
}

void Parser::RequireKeyword(IdentifierOrKeywordT keyword, const char* msg)
{
	if (!lexer.GetToken()->IsKeyword(keyword))
		ThrowSyntaxError(msg);
}

Parser::Parser(Lexer& lexer)
    : lexer(lexer)
{
}

ExprNodeP Parser::ParseExp()
{
	try {
		ListP<ExprNode*> assignment_exp_list;
		ExprNodeP assignment_exp1 = ParseAssignmentExp();
		assignment_exp_list.PushBack(assignment_exp1);
		while (lexer.GetToken()->IsOperator(OP_COMMA)) {
			lexer.NextToken();
			ExprNodeP assignment_exp = ParseAssignmentExp();
			assignment_exp_list.PushBack(assignment_exp);
		}
		if (assignment_exp_list.size() == 1)
			return assignment_exp_list.PopFront();
		else
			return ExprNodeP(new Exp(assignment_exp_list));
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParseAssignmentExp()
{
	try {
		ExprNodeP conditional_exp = ParseConditionalExp();
		BinaryExpClass binary_exp_class;
		OperatorT binary_operator;
		if (!is_assignment_operator(lexer.GetToken(),
			binary_exp_class, binary_operator))
		{
			return conditional_exp;
		}
		if (!conditional_exp->IsUnaryExp())
			ThrowSyntaxError(
				"Unary expression expected but conditional expression found");
		OperatorT assignment_operator =
			static_cast<Token_operator*>(lexer.GetToken())->Value();
		lexer.NextToken();
		ExprNodeP assignment_exp = ParseAssignmentExp();
		if (binary_exp_class != BINARY_EXP_CLASS_NONE) {
			assignment_exp = ExprNodeP(new BinaryExp(
				binary_exp_class, conditional_exp->CreateCopy(),
				binary_operator, assignment_exp));
		}
		return ExprNodeP(new AssignmentExp(conditional_exp, assignment_exp));
		//conditional_exp является unary_exp
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParseConditionalExp()
{
	try {
		ExprNodeP logical_or_exp = ParseBinaryExp(BINARY_EXP_CLASS_LOGICAL_OR);
		if (!lexer.GetToken()->IsOperator(OP_QUEST_MARK))
			return logical_or_exp;
		lexer.NextToken();
		ExprNodeP exp = ParseExp();
		if (!lexer.GetToken()->IsOperator(OP_COLON))
			ThrowSyntaxError("\':\' expected");
		lexer.NextToken();
		ExprNodeP conditional_exp = ParseConditionalExp();
		return ExprNodeP(new ConditionalExp(
			logical_or_exp, exp, conditional_exp));
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParseBinaryExp(BinaryExpClass binary_exp_class)
{
	try {
		ListP<ExprNode*> binary_exp_deque;
		std::vector<OperatorT> binary_op_list;
		while (1) {
			ExprNodeP binary_exp(0);
			if (binary_exp_class == BINARY_EXP_CLASS_MULT)
				binary_exp = ParseUnaryExp();
			else
				binary_exp = ParseBinaryExp(
					(BinaryExpClass)(binary_exp_class+1));
			binary_exp_deque.PushBack(binary_exp);
			if (!is_binary_operator(binary_exp_class, lexer.GetToken()))
				break;
			OperatorT op = static_cast<Token_operator*>(
				lexer.GetToken())->Value();
			binary_op_list.push_back(op);
			lexer.NextToken();
		}

		std::vector<OperatorT>::iterator j = binary_op_list.begin();
		ExprNodeP binary_exp = binary_exp_deque.PopFront();
		for (std::vector<OperatorT>::iterator i = binary_op_list.begin();
			i != binary_op_list.end(); ++i)
		{
			ExprNodeP binary_exp2 = binary_exp_deque.PopFront();
			binary_exp = ExprNodeP(new BinaryExp(
				binary_exp_class, binary_exp, *i, binary_exp2));
		}
		return binary_exp;
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParseUnaryExp()
{
	try {
		if (lexer.GetToken()->IsOperator(OP_PLUS_PLUS) ||
		lexer.GetToken()->IsOperator(OP_MINUS_MINUS)) {
			OperatorT inc_dec_operator = static_cast<Token_operator*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			ExprNodeP unary_exp = ParseUnaryExp();
			return ExprNodeP(new UnaryExpIncDec(inc_dec_operator, unary_exp));
		}
		else if (is_unary_operator(lexer.GetToken())) {
			OperatorT unary_operator = static_cast<Token_operator*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			ExprNodeP unary_exp = ParseUnaryExp();
			return ExprNodeP(
				new UnaryExpUnaryOperator(unary_operator, unary_exp));
		}
		else {
			ExprNodeP postfix_exp = ParsePostfixExp();
			return postfix_exp;
		}
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParsePostfixExp()
{
	try {
		ExprNodeP postfix_exp = ParsePrimaryExp();
		while (1) {
			if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_SQUARE_BRACKET)) {
				lexer.NextToken();
				ExprNodeP exp = ParseExp();
				if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_SQUARE_BRACKET))
					ThrowSyntaxError("\']\' expected");
				postfix_exp = ExprNodeP(
					new PostfixExpArrayIndex(postfix_exp, exp));
				lexer.NextToken();
			}
			else if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_ROUND_BRACKET)) {
				lexer.NextToken();
				ListP<ExprNode*> argument_exp_list;
				if (lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
					lexer.NextToken();
				else {
					while (1) {
						ExprNodeP assignment_exp = ParseAssignmentExp();
						argument_exp_list.PushBack(assignment_exp);
						if (!lexer.GetToken()->IsOperator(OP_COMMA))
							break;
						lexer.NextToken();
					}
					if (!lexer.GetToken()->IsDelimiter(
						DELIM_RIGHT_ROUND_BRACKET))
					{
						ThrowSyntaxError("\')\' expected");
					}
					lexer.NextToken();
				}
				postfix_exp = ExprNodeP(new PostfixExpFuncCall(
					postfix_exp, argument_exp_list));
			}
			else if (lexer.GetToken()->IsOperator(OP_POINT) ||
			lexer.GetToken()->IsOperator(OP_ARROW)) {
				OperatorT point_arrow_operator = static_cast<Token_operator*>
					(lexer.GetToken())->Value();
				lexer.NextToken();
				if (!lexer.GetToken()->IsIdentifier())
					ThrowSyntaxError("Identifier expected");
				std::string id_text = lexer.GetToken()->Text();
				if (point_arrow_operator == OP_ARROW)
				{
					postfix_exp = ExprNodeP(
						new UnaryExpUnaryOperator(OP_STAR, postfix_exp));
				}
				postfix_exp = ExprNodeP(
					new PostfixExpPoint(postfix_exp, id_text));
				lexer.NextToken();
			}
			else if (lexer.GetToken()->IsOperator(OP_PLUS_PLUS) ||
			lexer.GetToken()->IsOperator(OP_MINUS_MINUS)) {
				postfix_exp = ExprNodeP(new PostfixExpIncDec(postfix_exp,
					static_cast<Token_operator*>(lexer.GetToken())->Value()));
				lexer.NextToken();
			}
			else
				break;
		}
		return postfix_exp;
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

ExprNodeP Parser::ParsePrimaryExp()
{
	try {
		if (lexer.GetToken()->IsIdentifier()) {
			PrimaryExp* primary_exp = 0;
			const std::string& id_text = lexer.GetToken()->Text();
			Decl1* decl1 = sym_tables_stack.FindDecl1(id_text);
			if (!decl1)
				ThrowTypesError("Undeclarated identifier");
			switch (decl1->GetDecl1Class()) {
				case DECL1_CLASS_VAR:
					primary_exp = new PrimaryExpVar(
						static_cast<DeclVar*>(decl1), id_text);
					break;
				case DECL1_CLASS_TYPEDEF_NAME:
					ThrowTypesError("Unexpected typedef_name");
					break;
				case DECL1_CLASS_ENUM_CONST:
					primary_exp = new PrimaryExpIntConst(
						static_cast<DeclEnumConst*>(decl1)->value);
					break;
				case DECL1_CLASS_FUNC:
					primary_exp = new PrimaryExpFunc(
						static_cast<DeclFunc*>(decl1), id_text);
					break;
			}
			lexer.NextToken();
			return ExprNodeP(primary_exp);
		}
		else if (lexer.GetToken()->Tok_cl() == TOKEN_CLASS_INT_CONST) {
			int const_value = static_cast<Token_int_const*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			return ExprNodeP(new PrimaryExpIntConst(const_value));
		}
		else if (lexer.GetToken()->Tok_cl() == TOKEN_CLASS_CHAR_CONST) {
			char const_value = static_cast<Token_char_const*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			return ExprNodeP(new PrimaryExpIntConst(const_value));
		}
		else if (lexer.GetToken()->Tok_cl() == TOKEN_CLASS_REAL_CONST) {
			double const_value = static_cast<Token_real_const*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			return ExprNodeP(new PrimaryExpRealConst(const_value));
		}
		else if (lexer.GetToken()->Tok_cl() == TOKEN_CLASS_STRING_CONST) {
			std::string const_value = static_cast<Token_string_const*>
				(lexer.GetToken())->Value();
			lexer.NextToken();
			return ExprNodeP(new PrimaryExpStringConst(const_value));
		}
		else if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_ROUND_BRACKET)) {
			lexer.NextToken();
			ExprNodeP exp = ParseExp();
			if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
				ThrowSyntaxError("\')\' expected");
			lexer.NextToken();
			return exp;
		}
		else
			ThrowSyntaxError("Primary expression expected");
	}
	catch (TypesError t) {
		ThrowTypesError(t.Message());
	}
}

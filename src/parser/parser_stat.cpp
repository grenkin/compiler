#include "parser.h"

StatP Parser::ParseStat()
{
	if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE))
		return StatP(ParseCompoundStat());
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_IF))
		return ParseSelectionStat();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_WHILE))
		return ParseIterationStatWhile();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_DO))
		return ParseIterationStatDoWhile();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_FOR))
		return ParseIterationStatFor();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_CONTINUE))
		return ParseJumpStatContinue();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_BREAK))
		return ParseJumpStatBreak();
	else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_RETURN))
		return ParseJumpStatReturn();
	else
		return ParseExpStat();
}

StatP Parser::ParseExpStat()
{
	if (lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
		lexer.NextToken();
		return StatP(new ExpStat());
	}
	else {
		std::auto_ptr<ExpStat> exp_stat(new ExpStat());
		exp_stat->exp = ParseExp();
		RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
		lexer.NextToken();
		return exp_stat;			
	}
}

CompoundStatP Parser::ParseCompoundStat(ParamList* param_list)
//Если param_list != 0, то составной оператор представляет собой тело функции
//и param_list -- список параметров этой функции.
{
	//текущая лексема == '{'
	lexer.NextToken();
	CompoundStatP compound_stat(new CompoundStat());
	sym_tables_stack.PushSymTableBlock(compound_stat->sym_table);
	if (param_list) {
		/* Параметры в определении функции добавляются в таблицу символов,
		   блока, представляющего собой тело функции. */
		for (ParamList::iterator i = param_list->begin();
			i != param_list->end(); ++i)
		{
			ExprType expr_type2 = (*i)->type.CreateCopy();
			DeclVar* p = new DeclVar(expr_type2, STOR_CL_NONE, DECL_VAR_CLASS_PARAM);
			sym_tables_stack.InsertDecl1((*i)->name, std::auto_ptr<Decl1>(p));
		}
	}
	ParseDeclList();
	//Разбор stat_list...
	while (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_BRACE))	
		compound_stat->stat_list.PushBack(ParseStat());
	//текущая лексема == '}'
	lexer.NextToken();
	sym_tables_stack.PopSymTableBlock();
	return compound_stat;
}

StatP Parser::ParseSelectionStat()
{
	//текущая лексема == 'if'
	lexer.NextToken();
	std::auto_ptr<SelectionStat> selection_stat(new SelectionStat());
	RequireDelimiter(DELIM_LEFT_ROUND_BRACKET, "\'(\' expected");
	lexer.NextToken();
	selection_stat->exp = ParseExp();
	RequireDelimiter(DELIM_RIGHT_ROUND_BRACKET, "\')\' expected");
	lexer.NextToken();
	selection_stat->stat1 = ParseStat();
	if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_ELSE)) {
		lexer.NextToken();
		selection_stat->stat2 = ParseStat();
	}
	return selection_stat;
}

StatP Parser::ParseIterationStatWhile()
{
	//текущая лексема == 'while'
	lexer.NextToken();
	std::auto_ptr<IterationStatWhile> iteration_stat(new IterationStatWhile());
	RequireDelimiter(DELIM_LEFT_ROUND_BRACKET, "\'(\' expected");
	lexer.NextToken();
	iteration_stat->exp = ParseExp();
	RequireDelimiter(DELIM_RIGHT_ROUND_BRACKET, "\')\' expected");
	lexer.NextToken();
	iteration_stat->stat = ParseStat();
	return iteration_stat;
}

StatP Parser::ParseIterationStatDoWhile()
{
	//текущая лексема == 'do'
	lexer.NextToken();
	std::auto_ptr<IterationStatDoWhile> iteration_stat(new IterationStatDoWhile());
	iteration_stat->stat = ParseStat();
	RequireKeyword(IDENT_OR_KEYWORD_WHILE, "\'while\' expected");
	lexer.NextToken();
	RequireDelimiter(DELIM_LEFT_ROUND_BRACKET, "\'(\' expected");
	lexer.NextToken();
	iteration_stat->exp = ParseExp();
	RequireDelimiter(DELIM_RIGHT_ROUND_BRACKET, "\')\' expected");
	lexer.NextToken();
	RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	lexer.NextToken();
	return iteration_stat;
}

StatP Parser::ParseIterationStatFor()
{
	//текущая лексема == 'for'
	lexer.NextToken();
	std::auto_ptr<IterationStatFor> iteration_stat(new IterationStatFor());
	RequireDelimiter(DELIM_LEFT_ROUND_BRACKET, "\'(\' expected");
	lexer.NextToken();
	if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
		iteration_stat->exp1 = ParseExp();
		RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	}
	//текущая лексема == ';'
	lexer.NextToken();
	if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
		iteration_stat->exp2 = ParseExp();
		RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	}
	//текущая лексема == ';'
	lexer.NextToken();
	if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET)) {
		iteration_stat->exp3 = ParseExp();
		RequireDelimiter(DELIM_RIGHT_ROUND_BRACKET, "\')\' expected");
	}
	//текущая лексема == ')'
	lexer.NextToken();
	iteration_stat->stat = ParseStat();
	return iteration_stat;
}

StatP Parser::ParseJumpStatContinue()
{
	//текущая лексема == 'continue'
	lexer.NextToken();
	std::auto_ptr<JumpStatContinue> jump_stat(new JumpStatContinue());
	RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	//текущая лексема == ';'
	lexer.NextToken();
	return jump_stat;
}

StatP Parser::ParseJumpStatBreak()
{
	//текущая лексема == 'break'
	lexer.NextToken();
	std::auto_ptr<JumpStatBreak> jump_stat(new JumpStatBreak());
	RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	//текущая лексема == ';'
	lexer.NextToken();
	return jump_stat;
}

StatP Parser::ParseJumpStatReturn()
{
	//текущая лексема == 'return'
	lexer.NextToken();
	std::auto_ptr<JumpStatReturn> jump_stat(new JumpStatReturn());
	if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
		jump_stat->exp = ParseExp();
		RequireDelimiter(DELIM_SEMICOLON, "\';\' expected");
	}
	//текущая лексема == ';'
	lexer.NextToken();
	return jump_stat;
}

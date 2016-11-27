#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "..\lexer\lexer.h"
#include "tr_unit.h"
#include "..\errors\errors.h"

class Parser {
    Lexer& lexer;
	SymTablesStack sym_tables_stack;

    ExprNodeP ParseExp();
    ExprNodeP ParseAssignmentExp();
    ExprNodeP ParseConditionalExp();
    ExprNodeP ParseBinaryExp(BinaryExpClass);
    ExprNodeP ParseUnaryExp();
    ExprNodeP ParsePostfixExp();
    ExprNodeP ParsePrimaryExp();

	void ParseDeclList();
	void ParseDecl();
	void ParseStructDecl(int&);
	std::auto_ptr<ParamDecl> ParseParamDecl();
	ExprType ParseDeclSpecs(StorageClassSpec*, bool&, bool forbid_new_decl2 = false);
	std::auto_ptr<StructSpec> ParseStructSpec(bool&, bool forbid_new_decl2 = false);
	std::auto_ptr<EnumSpec> ParseEnumSpec(bool forbid_new_decl2 = false);
	AbstractDeclarator ParseDeclarator(std::string&);
	std::vector<TypeQualifiers> ParsePointer();
	AbstractDeclarator ParseDeclaratorSuffix();
	ParamList ParseParamList();

	StatP ParseStat();
	StatP ParseExpStat();
	CompoundStatP ParseCompoundStat(ParamList* param_list = 0);
	StatP ParseSelectionStat();
	StatP ParseIterationStatWhile();
	StatP ParseIterationStatDoWhile();
	StatP ParseIterationStatFor();
	StatP ParseJumpStatContinue();	
	StatP ParseJumpStatBreak();
	StatP ParseJumpStatReturn();

    bool IsDeclStartToken(Token*);
	void ThrowSyntaxError(std::string);
	void ThrowTypesError(std::string);
	void RequireDelimiter(DelimiterT, const char*);
	void RequireKeyword(IdentifierOrKeywordT, const char*);
public:
    Parser(Lexer&);
	TranslationUnit ParseTranslationUnit();
};

#endif // PARSER_H_INCLUDED

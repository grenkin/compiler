#include "parser.h"

TranslationUnit Parser::ParseTranslationUnit()
//translation_unit ::= external_decl |
//                     translation_unit external_decl
//external_decl ::= function_definition |
//                  decl
//function_definition ::= spec_qualifier_list declarator compound_stat
//decl ::= decl_specs declarator_list ';' |
//         decl_specs                 ';'
/* ƒополнительные услови¤
	1) ƒл¤ каждой функции должно быть ровно одно определение.
	2) “ип "функци¤" нельз¤ получить посредством typedef.
	3) ѕеременные, объ¤вл¤емые вне функций, считаютс¤ статическими.
	4) ¬ качестве спецификатора класса пам¤ти во внешнем объ¤влении можно
	   использовать только typedef.
    5) ѕараметры в определении функции добавл¤ютс¤ в таблицу символов блока,
	   представл¤ющего собой тело функции.
    6) ¬ случае decl_specs ';' спецификатор типа (type_spec) должен
	   объ¤вл¤ть метку структуры или задавать элементы перечислени¤.
    7) Ќедопустимо объ¤вление переменной неполного типа.
	8) Ќельз¤ объ¤вить переменную типа void.
	9) ≈сли param_list не состоит из единственного слова void, показывающего
	   отсутствие параметров у функции, то в каждом описателе в param_list
	   об¤зан присутствовать идентификатор.
    10) ќписатель должен быть корректным.
*/
{
	TranslationUnit translation_unit;

	ExprType expr_type_void, expr_type_int, expr_type_float, expr_type_pchar;
	ParamList param_list;
	expr_type_void.SetVoid();
	expr_type_int.SetInt();
	expr_type_float.SetFloat();
	expr_type_pchar.SetChar();
	expr_type_pchar.MakePointer();
	param_list.PushBack(std::auto_ptr<ParamDecl>(new ParamDecl(expr_type_int)));
	translation_unit.global_sym_table.InsertDeclFunc(
		"print_int", expr_type_void.CreateCopy(), param_list, translation_unit);
	param_list.PushBack(std::auto_ptr<ParamDecl>(new ParamDecl(expr_type_float)));
	translation_unit.global_sym_table.InsertDeclFunc(
		"print_float", expr_type_void.CreateCopy(), param_list, translation_unit);
	param_list.PushBack(std::auto_ptr<ParamDecl>(new ParamDecl(expr_type_pchar)));
	translation_unit.global_sym_table.InsertDeclFunc(
		"print_string", expr_type_void.CreateCopy(), param_list, translation_unit);

	sym_tables_stack.PushSymTableBlock(translation_unit.global_sym_table);
	while (lexer.GetToken()->Tok_cl() != TOKEN_CLASS_END_OF_FILE) {
		//–азбор external_decl...
		StorageClassSpec storage_class_spec;
		bool flag1;
		ExprType expr_type = ParseDeclSpecs(&storage_class_spec, flag1);
		if (storage_class_spec == STORAGE_CLASS_SPEC_STATIC) // 4)
			ThrowSyntaxError("Unexpected \'static\' in external_decl");
		if (lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
			//decl ::= decl_specs ';'
			if (!flag1) // 6)
				ThrowSyntaxError("Declarator expected but \';\' found");
			lexer.NextToken();
		}
		else {
			//function_definition ::= spec_qualifier_list declarator compound_stat
			//decl ::= decl_specs declarator_list ';'
			AbstractDeclarator abstract_declarator;
			std::string id;
			abstract_declarator = ParseDeclarator(id);
			if (id.empty())
				ThrowSyntaxError("Identifier expected");
			if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
				//function_definition ::= spec_qualifier_list declarator compound_stat
				if (abstract_declarator.empty() ||
					abstract_declarator.front()->GetAbstractDeclaratorElemClass() !=
					ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC)
				{
					ThrowSyntaxError("Syntax error before \'{\' token");
				}
				if (storage_class_spec != STORAGE_CLASS_SPEC_NONE)
					ThrowSyntaxError("Unexpected storage_class_spec");
				expr_type.AddAbstractDeclarator(abstract_declarator);
				if (!expr_type.CheckAbstractDeclaratorCorrectness()) // 10)
					ThrowSyntaxError("Incorrect declarator");
				std::auto_ptr<AbstractDeclaratorElem> p(
					expr_type.abstract_declarator.PopFront());
				ParamList param_list =
					static_cast<AbstractDeclaratorElemFunc*>(p.get())->param_list;
				// 9)
				if (!param_list.empty()) {
					for (ParamList::iterator i = param_list.begin();
						i != param_list.end(); ++i)
					{
						if ((*i)->name.empty())
							ThrowSyntaxError("Parameter name required");
					}
				}
				FunctionDefinition* fd =
					translation_unit.global_sym_table.InsertDeclFunc(
						id,	expr_type, param_list, translation_unit);
				if (fd->compound_stat.get()) // 1)
					ThrowSyntaxError("Function redifinition");	
				CompoundStatP compound_stat = ParseCompoundStat(&fd->param_list); // 5)
				fd->compound_stat = compound_stat;
			}
			else {
				//decl ::= decl_specs declarator_list ';'
				bool flag = false;
				while (1) {
					if (flag) {
						abstract_declarator = ParseDeclarator(id);
						if (id.empty())
							ThrowSyntaxError("Identifier expected");
					}
					flag = true;
					ExprType expr_type2 = expr_type.CreateCopy();
					expr_type2.AddAbstractDeclarator(abstract_declarator);
					if (expr_type2.IsFunc()) {
						if (storage_class_spec == STORAGE_CLASS_SPEC_TYPEDEF) // 2)
							ThrowSyntaxError("typedef function");
						std::auto_ptr<AbstractDeclaratorElem> p(
							expr_type2.abstract_declarator.PopFront());
						ParamList param_list =
							static_cast<AbstractDeclaratorElemFunc*>(p.get())->param_list;
						translation_unit.global_sym_table.InsertDeclFunc(
							id,	expr_type2, param_list, translation_unit);
					}
					else {
						if (!expr_type2.CheckAbstractDeclaratorCorrectness()) // 10)
							ThrowSyntaxError("Incorrect declarator");
						if (storage_class_spec == STORAGE_CLASS_SPEC_TYPEDEF) {
							DeclTypedefName* p = new DeclTypedefName(expr_type2);
							sym_tables_stack.InsertDecl1(id, std::auto_ptr<Decl1>(p));
						}
						else {
							if (expr_type2.Incomplete()) // 7)
								ThrowSyntaxError("Incomplete type variable declaration");
							if (expr_type2.IsVoid()) // 8)
								ThrowSyntaxError("Declared variable has type void");
							DeclVar* p = new DeclVar(expr_type2, STOR_CL_STATIC,
								DECL_VAR_CLASS_GLOBAL); // 3)
							sym_tables_stack.InsertDecl1(id, std::auto_ptr<Decl1>(p));
						}
					}
					if (!lexer.GetToken()->IsOperator(OP_COMMA))
						break;
					lexer.NextToken();
				}
				if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON))
					ThrowSyntaxError("\';\' expected");
				lexer.NextToken();
			}
		}
	}
	sym_tables_stack.PopSymTableBlock();
	for (MapP<FunctionDefinition*>::const_iterator i =
		translation_unit.func_def.begin(); i != translation_unit.func_def.end(); ++i)
	{
		if (i->first != "print_int" && i->first != "print_float" &&
			i->first != "print_string" &&
			!i->second->compound_stat.get()) // 1)
		{
			ThrowSyntaxError(
				std::string("There is no definition for function \'")+i->first+"\'");
		}
	}
	return translation_unit;
}

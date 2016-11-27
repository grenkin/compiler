#include "parser.h"

void Parser::ParseDeclList()
//Разбор decl_list, остановка после decl_list
//decl_list ::= decl |
//              decl_list decl
{
	while (IsDeclStartToken(lexer.GetToken())) {
		ParseDecl();
		lexer.NextToken();
	}
}

void Parser::ParseDecl()
//Разбор decl (в блоке), остановка на ';'
//decl ::= decl_specs declarator_list ';' |
//         decl_specs                 ';'
//declarator_list ::= declarator |
//                    declarator_list ',' declarator
/* Дополнительные условия
    1) В случае decl_specs ';' спецификатор типа (type_spec) должен
	   объявлять метку структуры или задавать элементы перечисления.
	2) Внутри блока не может находиться объявление функции.
	   Тип "функция" нельзя получить посредством typedef.
	3) Недопустимо объявление переменной неполного типа.
	4) Нельзя объявить переменную типа void.
	5) Описатель должен быть корректным.
*/
{
	StorageClassSpec storage_class_spec;
	bool flag1;
	ExprType expr_type = ParseDeclSpecs(&storage_class_spec, flag1);
	if (lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
		//decl ::= decl_specs ';'
		if (!flag1) // 1)
			ThrowSyntaxError("Declarator expected but \';\' found");
	}
	else {
		//decl ::= decl_specs declarator_list ';'
		AbstractDeclarator abstract_declarator;
		std::string id;
		while (1) {
			abstract_declarator = ParseDeclarator(id);
			if (id.empty())
				ThrowSyntaxError("Identifier expected");
			ExprType expr_type2 = expr_type.CreateCopy();
			expr_type2.AddAbstractDeclarator(abstract_declarator);
			if (expr_type2.IsFunc()) // 2)
				ThrowSyntaxError("Declaration of a function in the block");
			if (!expr_type2.CheckAbstractDeclaratorCorrectness()) // 5)
				ThrowSyntaxError("Incorrect declarator");
			if (storage_class_spec == STORAGE_CLASS_SPEC_TYPEDEF) {
				DeclTypedefName* p = new DeclTypedefName(expr_type2);
				sym_tables_stack.InsertDecl1(id, std::auto_ptr<Decl1>(p));
			}
			else {
				if (expr_type2.Incomplete()) // 3)
					ThrowSyntaxError("Incomplete type variable declaration");
				if (expr_type2.IsVoid()) // 4)
					ThrowSyntaxError("Declared variable has type void");
				DeclVar* p = new DeclVar(
					expr_type2,
					storage_class_spec == STORAGE_CLASS_SPEC_STATIC ?
					STOR_CL_STATIC : STOR_CL_NONE, DECL_VAR_CLASS_LOCAL);
				sym_tables_stack.InsertDecl1(id, std::auto_ptr<Decl1>(p));
			}
			if (!lexer.GetToken()->IsOperator(OP_COMMA))
				break;
			lexer.NextToken();
		}
		if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON))
			ThrowSyntaxError("\';\' expected");
	}
}

void Parser::ParseStructDecl(int& struct_size)
//Разбор struct_decl, остановка на ';'
//struct_decl ::= spec_qualifier_list declarator_list ';'
//declarator_list ::= declarator |
//                    declarator_list ',' declarator
/* Дополнительные условия
	1) Структура не может содержать элементов типа "функция".
	2) Структура не может содержать элементов неполного типа.
	3) Элемент структуры не может иметь тип void.
	4) Описатель должен быть корректным.
*/
{
	bool tmp;
	ExprType expr_type = ParseDeclSpecs(0, tmp);
	AbstractDeclarator abstract_declarator;
	std::string id;
	while (1) {
		abstract_declarator = ParseDeclarator(id);
		if (id.empty())
			ThrowSyntaxError("Identifier expected");
		ExprType expr_type2 = expr_type.CreateCopy();
		expr_type2.AddAbstractDeclarator(abstract_declarator);
		if (expr_type2.IsFunc()) // 1)
			ThrowSyntaxError("The structure field is a function");
		if (expr_type2.Incomplete()) // 2)
			ThrowSyntaxError("The structure field has incomplete type");
		if (expr_type2.IsVoid()) // 3)
			ThrowSyntaxError("The structure field has type void");
		if (!expr_type2.CheckAbstractDeclaratorCorrectness()) // 4)
			ThrowSyntaxError("Incorrect declarator");
		int field_size = expr_type2.GetSize();
		int field_offset = struct_size;
		struct_size += field_size;
		sym_tables_stack.InsertStructDecl(
			id, std::auto_ptr<StructDecl>(new StructDecl(expr_type2, field_offset)));
		if (!lexer.GetToken()->IsOperator(OP_COMMA))
			break;
		lexer.NextToken();
	}
	if (!lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON))
		ThrowSyntaxError("\';\' expected");
}

std::auto_ptr<ParamDecl> Parser::ParseParamDecl()
//Разбор param_decl, остановка после param_decl
//param_decl ::= spec_qualifier_list declarator
//               spec_qualifier_list abstract_declarator
//               spec_qualifier_list
/* Дополнительные условия
	1) Объявление параметра "массив типа..." трактуется как
	   "указатель на тип...". Аналогично, объявление параметра с типом
	   "функция, возвращающая тип..." трактуется как "указатель на функцию,
	   возвращающую тип...".
	2) Параметр не может иметь неполный структурный тип.
	3) Описатель должен быть корректным.
*/
{
	bool tmp;
	ExprType expr_type = ParseDeclSpecs(0, tmp, true);
	std::auto_ptr<ParamDecl> param_decl;
	if (lexer.GetToken()->IsOperator(OP_COMMA) ||
		lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
	{
		//param_decl ::= spec_qualifier_list
		param_decl.reset(new ParamDecl(expr_type));
	}
	else {
		//param_decl ::= spec_qualifier_list declarator |
		//               spec_qualifier_list abstract_declarator
		std::string id;
		AbstractDeclarator abstract_declarator = ParseDeclarator(id);
		expr_type.AddAbstractDeclarator(abstract_declarator);
		param_decl.reset(new ParamDecl(expr_type, id));
	}
	param_decl->type.PointerGeneration(); // 1)
	if (param_decl->type.Incomplete()) // 2)
		ThrowSyntaxError(
			"The parameter of a function has incomplete structure type");
	if (!param_decl->type.CheckAbstractDeclaratorCorrectness()) // 3)
		ThrowSyntaxError("Incorrect declarator");
	return std::auto_ptr<ParamDecl>(param_decl);
}

ExprType Parser::ParseDeclSpecs(StorageClassSpec* storage_class_spec,
	bool& flag1, bool forbid_new_decl2)
//Разбор decl_specs/spec_qualifier_list, остановка после
//Если storage_class_spec == 0, то производится разбор spec_qualifier_list,
//иначе -- decl_specs.
//Если спецификатор типа объявляет метку структуры или задаёт элементы
//перечисления, то flag1 присваивается true, в противном случае -- false.
//decl_specs ::= storage_class_spec decl_specs |
//               storage_class_spec |
//               type_spec decl_specs |
//               type_spec |
//               type_qualifier decl_specs |
//               type_qualifier
//storage_class_spec ::= 'static' | 'typedef'
//type_spec ::= 'void' | 'char' | 'int' | 'float' |
//              struct_spec |
//              enum_spec |
//              typedef_name
//type_qualifier ::= 'const'
//typedef_name ::= id
/* Дополнительные условия
    1) Единственность storage_class_spec.
	2) Единственность type_spec.
	3) Если в объявлении нет ни одного спецификатора типа, то
	   подразумевается тип int.
*/
{
	flag1 = false;
	ExprType expr_type;
	if (storage_class_spec)
		*storage_class_spec = STORAGE_CLASS_SPEC_NONE;
	TypeQualifiers type_qual = TYPE_QUAL_NONE;
	bool decl_specs_empty = true;
	while (1) {
		int k = -1;
		for (int i = 0; i < BASE_TYPES_NUMBER; ++i) {
			if (lexer.GetToken()->IsKeyword(BASE_TYPES_KEYWORDS[i])) {
				k = i;
				break;
			}
		}
		if (k != -1) {
			BaseTypeT base_type = (BaseTypeT)k;
			if (expr_type.type_spec.get() != 0) // 2)
				ThrowSyntaxError("Duplicated type_spec");
			expr_type.type_spec = std::auto_ptr<TypeSpec>(
				new BaseTypeSpec(base_type));
			lexer.NextToken();
		}
		else if (lexer.GetToken()->IsIdentifier()) {
			const std::string& id = lexer.GetToken()->Text();
			Decl1* decl1 = sym_tables_stack.FindDecl1(id);
			if (!decl1)
				break;
			if (decl1->GetDecl1Class() != DECL1_CLASS_TYPEDEF_NAME)
				break;
			//id -- typedef_name
			if (expr_type.type_spec.get() != 0) // 2)
				ThrowSyntaxError("Duplicated type_spec");
			ExprType expr_type2 =
				static_cast<DeclTypedefName*>(decl1)->type.CreateCopy();
			expr_type = expr_type2;
			//Нельзя присвоить type напрямую, так как в этом случае
			//произойдёт потеря данных из-за деструктивного копирования.
			lexer.NextToken();
		}
		else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_STATIC) ||
			lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_TYPEDEF))
		{
			if (!storage_class_spec)
				ThrowSyntaxError("Unexpected storage_class_spec");
			if (*storage_class_spec != STORAGE_CLASS_SPEC_NONE) // 1)
				ThrowSyntaxError("Duplicated storage_class_spec");
			if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_STATIC))
				*storage_class_spec = STORAGE_CLASS_SPEC_STATIC;
			else
				*storage_class_spec = STORAGE_CLASS_SPEC_TYPEDEF;
			lexer.NextToken();
		}
		else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_CONST)) {
			type_qual = TYPE_QUAL_CONST;
			lexer.NextToken();
		}
		else if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_STRUCT) ||
			lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_ENUM))
		{
			if (expr_type.type_spec.get() != 0) // 2)
				ThrowSyntaxError("Duplicated type_spec");
			if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_STRUCT))
				expr_type.type_spec = ParseStructSpec(flag1, forbid_new_decl2);
			else {
				expr_type.type_spec = ParseEnumSpec(forbid_new_decl2);
				flag1 = true;
			}
		}
		else
			break;
		decl_specs_empty = false;
	}
	if (decl_specs_empty)
		ThrowSyntaxError("decl_specs expected");
	if (!expr_type.type_spec.get()) // 3)
		expr_type.type_spec = std::auto_ptr<TypeSpec>(
			new BaseTypeSpec(BASE_TYPE_INT));
	if (type_qual == TYPE_QUAL_CONST)
		expr_type.type_qualifiers = TYPE_QUAL_CONST;
	return expr_type;
}

std::auto_ptr<StructSpec> Parser::ParseStructSpec(bool& contains_tag,
	bool forbid_new_decl2)
//Разбор struct_spec, остановка после struct_spec
//struct_spec ::= 'struct' id '{' struct_decl_list '}' |
//                'struct'    '{' struct_decl_list '}' |
//                'struct' id
//struct_decl_list ::= struct_decl |
//                     struct_decl_list struct_decl
{
	//текущая лексема == 'struct'
	contains_tag = false;
	lexer.NextToken();
	DeclTypeStruct* decl_type_struct = 0;
	if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
		//'struct' '{' struct_decl_list '}'
		//Создать новый анонимный тип struct
		if (forbid_new_decl2)
			ThrowSyntaxError("Struct declaration at this place is forbidden");
		decl_type_struct = new DeclTypeStruct();
		sym_tables_stack.InsertDecl2(std::auto_ptr<Decl2>(decl_type_struct));
	}
	else if (lexer.GetToken()->IsIdentifier()) {
		//'struct' id '{' struct_decl_list '}' |
		//'struct' id
		contains_tag = true;
		std::string id = lexer.GetToken()->Text();
		//Поиск объявления с меткой id...
		bool current_sym_table;
		Decl2* decl2 = sym_tables_stack.FindDecl2(id, &current_sym_table);
		Decl2Class decl2_class;
		if (decl2)
			decl2_class = decl2->GetDecl2Class();
		lexer.NextToken();
		if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
			//'struct' id '{' struct_decl_list '}'
			if (current_sym_table) {
				//В текущей таблице символов найдено объявление с меткой id
				if (decl2_class != DECL2_CLASS_STRUCT)
					ThrowSyntaxError("Using enum tag with keyword \'struct\'");
				decl_type_struct = static_cast<DeclTypeStruct*>(decl2);
				if (decl_type_struct->opened)
					ThrowSyntaxError("Struct redefinition");
			}
			else {
				//В текущей таблице символов нет объявления с меткой id
				//Создать новый тип struct id
				if (forbid_new_decl2)
					ThrowSyntaxError("Struct declaration at this place is forbidden");
				decl_type_struct = new DeclTypeStruct();
				sym_tables_stack.InsertDecl2(
					id, std::auto_ptr<Decl2>(decl_type_struct));
			}
		}
		else {
			//'struct' id
			if (current_sym_table) {
				//В текущей таблице символов найдено объявление с меткой id
				if (decl2_class != DECL2_CLASS_STRUCT)
					ThrowSyntaxError("Using enum tag with keyword \'struct\'");
				decl_type_struct = static_cast<DeclTypeStruct*>(decl2);
			}
			else {
				//В текущей таблице символов нет объявления с меткой id
				if (lexer.GetToken()->IsDelimiter(DELIM_SEMICOLON)) {
					//'struct' id ';'
					//Создать новый тип struct id
					if (forbid_new_decl2)
						ThrowSyntaxError("Struct declaration at this place is forbidden");
					decl_type_struct = new DeclTypeStruct();
					sym_tables_stack.InsertDecl2(
						id, std::auto_ptr<Decl2>(decl_type_struct));
				}
				else {
					//'struct' id ...
					if (!decl2) {
						//В других таблицах символов также нет
						//объявления с меткой id
						//Создать новый тип struct id
						if (forbid_new_decl2)
							ThrowSyntaxError("Struct declaration at this place is forbidden");
						decl_type_struct = new DeclTypeStruct();
						sym_tables_stack.InsertDecl2(
							id, std::auto_ptr<Decl2>(decl_type_struct));
					}
					else {
						//В другой таблице символов есть объявление с меткой id
						if (decl2_class != DECL2_CLASS_STRUCT)
							ThrowSyntaxError("Using enum tag with keyword \'struct\'");
						decl_type_struct = static_cast<DeclTypeStruct*>(decl2);
					}
				}
			}
		}
	}
	else
		ThrowSyntaxError("Unexpected token after \'struct\'");
	if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
		//'struct' id '{' struct_decl_list '}' |
		//'struct'    '{' struct_decl_list '}'
		//текущая лексема == '{'
		if (!decl_type_struct->incomplete || decl_type_struct->opened)
			ThrowSyntaxError("Struct redefinition");
		//Добавить таблицу символов структуры в стек
		sym_tables_stack.PushSymTableStruct(decl_type_struct->sym_table);
		decl_type_struct->opened = true;
		lexer.NextToken();
		//Разбор struct_decl_list...
		do {
			ParseStructDecl(decl_type_struct->struct_size);
			lexer.NextToken();
		} while (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_BRACE));
		lexer.NextToken();
		decl_type_struct->incomplete = false;
		sym_tables_stack.PopSymTableStruct();
	}
	return std::auto_ptr<StructSpec>(new StructSpec(decl_type_struct));
}

std::auto_ptr<EnumSpec> Parser::ParseEnumSpec(bool forbid_new_decl2)
//Разбор enum_spec, остановка после enum_spec
//enum_spec ::= 'enum' id '{' enumerator_list '}' |
//              'enum'    '{' enumerator_list '}' |
//              'enum' id
//enumerator_list ::= enumerator |
//                    enumerator_list ',' enumerator
//enumerator ::= id |
//               id '=' const_exp
{
	//текущая лексема == 'enum'
	lexer.NextToken();
	DeclTypeEnum* decl_type_enum = 0;
	if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
		//'enum' '{' enumerator_list '}'
		//Создать новый анонимный тип enum
		if (forbid_new_decl2)
			ThrowSyntaxError("Enum declaration at this place is forbidden");
		decl_type_enum = new DeclTypeEnum();
		sym_tables_stack.InsertDecl2(std::auto_ptr<Decl2>(decl_type_enum));
	}
	else if (lexer.GetToken()->IsIdentifier()) {
		//'enum' id '{' enumerator_list '}' |
		//'enum' id
		std::string id = lexer.GetToken()->Text();
		//Поиск объявления с меткой id...
		bool current_sym_table;
		Decl2* decl2 = sym_tables_stack.FindDecl2(id, &current_sym_table);
		lexer.NextToken();
		if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
			//'enum' id '{' enumerator_list '}'
			if (current_sym_table)
				ThrowSyntaxError("Enum redefinition");
			//Создать новый тип enum id
			if (forbid_new_decl2)
				ThrowSyntaxError("Enum declaration at this place is forbidden");
			decl_type_enum = new DeclTypeEnum();
			sym_tables_stack.InsertDecl2(
				id, std::auto_ptr<Decl2>(decl_type_enum));
		}
		else {
			//'enum' id
			if (!decl2) //объявление enum id не найдено
				ThrowSyntaxError("Incomplete enum");
			if (decl2->GetDecl2Class() != DECL2_CLASS_ENUM)
				ThrowSyntaxError("Using struct tag with keyword \'enum\'");
			decl_type_enum = static_cast<DeclTypeEnum*>(decl2);
		}
	}
	else
		ThrowSyntaxError("Unexpected token after \'enum\'");
	if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_BRACE)) {
		//'enum' id '{' enumerator_list '}' |
		//'enum'    '{' enumerator_list '}'
		//текущая лексема == '{'
		//Разбор enumerator_list...
		int counter = 0;
		do {
			lexer.NextToken();
			//Разбор enumerator...
			if (!lexer.GetToken()->IsIdentifier())
				ThrowSyntaxError("Identifier expected");
			const std::string& id = lexer.GetToken()->Text();
			sym_tables_stack.InsertDecl1(id, std::auto_ptr<Decl1>(
				new DeclEnumConst(counter++)));
			lexer.NextToken();
		} while (lexer.GetToken()->IsOperator(OP_COMMA));
		if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_BRACE))
			ThrowSyntaxError("\'}\' expected");
		lexer.NextToken();
	}
	return std::auto_ptr<EnumSpec>(new EnumSpec(decl_type_enum));
}

AbstractDeclarator Parser::ParseDeclarator(std::string& id)
//Разбор declarator/abstract_declarator, остановка после
//declarator ::= pointer direct_declarator |
//                       direct_declarator
//direct_declarator ::= id                                  |
//                      '(' declarator ')'                  |
//					    direct_declarator '[' const_exp ']' |
//					    direct_declarator '['           ']' |
//					    direct_declarator '(' param_list ')'
//abstract_declarator ::= pointer	                         |
//                        pointer direct_abstract_declarator |
//						          direct_abstract_declarator
//direct_abstract_declarator ::= '(' abstract_declarator ')'                   |
//                               direct_abstract_declarator '[' const_exp ']'  |
//							                                '[' const_exp ']'  |
//							     direct_abstract_declarator '['           ']'  |
//							                                '['           ']'  |
//							     direct_abstract_declarator '(' param_list ')' |
//							                                '(' param_list ')'
//Если abstract_declarator, то id == "".
{
	AbstractDeclarator abstract_declarator;
	std::vector<TypeQualifiers> pointer = ParsePointer();
	if (lexer.GetToken()->IsIdentifier()) {
		id = lexer.GetToken()->Text();
		lexer.NextToken();
	}
	else if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_ROUND_BRACKET)) {
		//'(' declarator ')' | '(' abstract_declarator ')' | '(' param_list ')'
		lexer.NextToken();
		if (IsDeclStartToken(lexer.GetToken())) {
			//'(' param_list ')'
			id.clear();
			ParamList param_list = ParseParamList();
			if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
				ThrowSyntaxError("\')\' expected");
			lexer.NextToken();
			AbstractDeclaratorElemFunc* p = new AbstractDeclaratorElemFunc(param_list);
			abstract_declarator.PushBack(std::auto_ptr<AbstractDeclaratorElem>(p));
		}
		else {
			//'(' declarator ')' | '(' abstract_declarator ')'
			abstract_declarator = ParseDeclarator(id);
			if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
				ThrowSyntaxError("\')\' expected");
			lexer.NextToken();
		}
	}
	else if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_SQUARE_BRACKET))
		id.clear();
	else {
		if (pointer.empty())
			ThrowSyntaxError("Unexpected token");
		else
			id.clear();
	}
	AbstractDeclarator suf = ParseDeclaratorSuffix();
	AddDeclaratorSuffix(abstract_declarator, suf);
	AddPointer(abstract_declarator, pointer);
	return abstract_declarator;
}

std::vector<TypeQualifiers> Parser::ParsePointer()
//Разбор pointer, остановка после
//pointer ::= '*' type_qualifier_list         |
//            '*'                             |
//			  '*' type_qualifier_list pointer |
//			  '*'                     pointer
{
	std::vector<TypeQualifiers> pointer;
	while (lexer.GetToken()->IsOperator(OP_STAR)) {
		lexer.NextToken();
		TypeQualifiers type_qual = TYPE_QUAL_NONE;
		if (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_CONST)) {
			type_qual = TYPE_QUAL_CONST;
			do {
				lexer.NextToken();
			} while (lexer.GetToken()->IsKeyword(IDENT_OR_KEYWORD_CONST));
		}
		pointer.push_back(type_qual);
	}
	return pointer;
}

AbstractDeclarator Parser::ParseDeclaratorSuffix()
//Разбор declarator_suffix, остановка после
//declarator_suffix может быть пустым
//declarator_suffix ::= declarator_suffix '[' const_exp ']'  |
//							              '[' const_exp ']'  |
//					    declarator_suffix '['           ']'  |
//							              '['           ']'  |
//					    declarator_suffix '(' param_list ')' |
//							              '(' param_list ')'
{
	AbstractDeclarator abstract_declarator;
	while (1) {
		if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_SQUARE_BRACKET)) {
			//'[' const_exp ']' | '[' ']'
			lexer.NextToken();
			int const_exp_value = 0;
			if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_SQUARE_BRACKET)) {
				//'[' const_exp ']'
				ExprNodeP const_exp = ParseExp();
				if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_SQUARE_BRACKET))
					ThrowSyntaxError("\']\' expected");
				if (!const_exp->is_const_exp)
					ThrowSyntaxError("const_exp expected");
				const_exp_value = const_exp->const_exp_value;
				if (const_exp_value <= 0)
					ThrowSyntaxError("Value of the constant expression must be more than 0");
			}
			//текущая лексема == ']'
			AbstractDeclaratorElemArray* p =
				new AbstractDeclaratorElemArray(const_exp_value);
			abstract_declarator.PushBack(
				std::auto_ptr<AbstractDeclaratorElem>(p));
			lexer.NextToken();
		}
		else if (lexer.GetToken()->IsDelimiter(DELIM_LEFT_ROUND_BRACKET)) {
			lexer.NextToken();
			ParamList param_list = ParseParamList();
			if (!lexer.GetToken()->IsDelimiter(DELIM_RIGHT_ROUND_BRACKET))
				ThrowSyntaxError("\')\' expected");
			AbstractDeclaratorElemFunc* p = new AbstractDeclaratorElemFunc(param_list);
			abstract_declarator.PushBack(std::auto_ptr<AbstractDeclaratorElem>(p));
			lexer.NextToken();
		}
		else
			break;
	}
	return abstract_declarator;
}

ParamList Parser::ParseParamList()
//Разбор param_list, остановка после
//param_list ::= param_decl |
//               param_list ',' param_decl
/* Дополнительные условия
    1) Если один из параметров имеет тип void, то:
	   а) этот параметр должен быть единственным в списке,
	   б) имя параметра должно отсутствовать.
    2) Имена параметров не должны повторяться.
*/
{
	ParamList param_list;
	while (1) {
		param_list.PushBack(ParseParamDecl());
		if (!lexer.GetToken()->IsOperator(OP_COMMA))
			break;
		lexer.NextToken();
	}
	// 1)
	for (ParamList::iterator i = param_list.begin();
		i != param_list.end(); ++i)
	{
		if ((*i)->type.IsVoid()) {
			if (param_list.size() != 1 || !(*i)->name.empty())
				ThrowSyntaxError("Incorrect param_list");
		}
	}
	// 2)
	for (ParamList::iterator i = param_list.begin();
		i != param_list.end(); ++i)
	{
		ParamList::iterator j = i;
		++j;
		for (; j != param_list.end(); ++j) {
			if (!(*i)->name.empty() && (*i)->name == (*j)->name)
				ThrowSyntaxError("Duplicated names of parameters");
		}
	}
	if (param_list.front()->type.IsVoid())
		param_list.clear();
	return param_list;
}

bool Parser::IsDeclStartToken(Token* token)
//Может ли данная лексема служить началом объявления
{
	for (int i = 0; i < BASE_TYPES_NUMBER; ++i) {
		if (token->IsKeyword(BASE_TYPES_KEYWORDS[i]))
			return true;
	}
	if (token->IsKeyword(IDENT_OR_KEYWORD_STATIC) ||
		token->IsKeyword(IDENT_OR_KEYWORD_TYPEDEF) ||
		token->IsKeyword(IDENT_OR_KEYWORD_CONST) ||
		token->IsKeyword(IDENT_OR_KEYWORD_STRUCT) ||
		token->IsKeyword(IDENT_OR_KEYWORD_ENUM))
	{
		return true;
	}
	if (token->IsIdentifier()) {
		const std::string& id = token->Text();
		Decl1* decl1 = sym_tables_stack.FindDecl1(id);
		if (decl1 && decl1->GetDecl1Class() == DECL1_CLASS_TYPEDEF_NAME)
			return true;
	}
	return false;
}

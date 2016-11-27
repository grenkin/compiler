#include <iostream>

#include "..\lexer\lexer.h"
#include "..\parser\parser.h"
#include "..\generator\asm_program.h"

namespace {

	void PrintErrorMessage(CompilerError& error, Lexer& lexer, std::ostream& out)
	{
	    const int COMPILER_ERROR_CLASSES_NUMBER = 5;
        const char* errors_str[COMPILER_ERROR_CLASSES_NUMBER] = {
			"Lexer error", "Syntax error", "Syntax error",
			"Types error", "Generator error"};
        out << errors_str[error.ErrorClass()] << '\n';
        out << error.Message() << '\n';
		int line, pos;
		if (error.ErrorClass() == COMPILER_ERROR_CLASS_ID_REDECL) {
			line = lexer.GetToken()->Line();
			pos = lexer.GetToken()->Pos();
		}
		else {
			line = error.Line();
			pos = error.Pos();
		}
		if (error.ErrorClass() != COMPILER_ERROR_CLASS_GENERATOR)
			out << "line " << line << ", pos " << pos << '\n';
        if (error.ErrorClass() == COMPILER_ERROR_CLASS_LEXER)
            out << "Text: " << dynamic_cast<LexerError&>(error).Text() << '\n';
	}
}

void RunLexer(const char* file_name, std::ostream& out)
{
    ThrowLexerError = false;

    const int TOKEN_CLASSES_NUMBER = 10;
    const unsigned int TOKEN_NAME_LENGTH = 22;
    char tok_names[TOKEN_CLASSES_NUMBER][TOKEN_NAME_LENGTH+1] = {
            "Begin of file", "End of file", "Error", "Integer constant",
            "Real constant", "Character constant", "String constant",
            "Identifier or keyword", "Operator", "Delimiter"};
    for (int i = 0; i < TOKEN_CLASSES_NUMBER; ++i) {
        while (strlen(tok_names[i]) < TOKEN_NAME_LENGTH)
            strcat(tok_names[i], ".");
    }

    out << "File: " << file_name << '\n';
    out << "Token class          " << " text (line, pos) = value" << '\n';
    out << "----------------------------------------" << '\n';
    Lexer lexer(file_name);
    Token* token = lexer.GetToken();
    while (!(token->Tok_cl() == TOKEN_CLASS_END_OF_FILE ||
    token->Tok_cl() == TOKEN_CLASS_ERROR)) {
        lexer.NextToken();
        token = lexer.GetToken();
        out << tok_names[token->Tok_cl()];
        out << " " << token->Text();
        out << " (" << token->Line() << ", " << token->Pos() << ")";
        out << " = ";
        switch (token->Tok_cl()) {
            case TOKEN_CLASS_BEGIN_OF_FILE:         break;
            case TOKEN_CLASS_END_OF_FILE:           break;
            case TOKEN_CLASS_ERROR:                 out << static_cast<Token_error*>(token)->Value(); break;
            case TOKEN_CLASS_INT_CONST:             out << static_cast<Token_int_const*>(token)->Value(); break;
            case TOKEN_CLASS_REAL_CONST:            out << static_cast<Token_real_const*>(token)->Value(); break;
            case TOKEN_CLASS_CHAR_CONST:            out << '\'' << static_cast<Token_char_const*>(token)->Value() << '\''; break;
            case TOKEN_CLASS_STRING_CONST:          out << '\"' << static_cast<Token_string_const*>(token)->Value() << '\"'; break;
            case TOKEN_CLASS_IDENTIFIER_OR_KEYWORD: out << static_cast<Token_ident_or_keyword*>(token)->Value(); break;
            case TOKEN_CLASS_OPERATOR:              out << static_cast<Token_operator*>(token)->Value(); break;
            case TOKEN_CLASS_DELIMITER:             out << static_cast<Token_delimiter*>(token)->Value(); break;
        }
        out << '\n';
    }
}

void RunParser(const char* file_name, std::ostream& out)
{
    ThrowLexerError = true;

    Lexer lexer(file_name);
    lexer.NextToken();
    Parser parser(lexer);
    try {
		TranslationUnit translation_unit = parser.ParseTranslationUnit();
		translation_unit.Print(0, out);
	}
    catch (CompilerError& error) {
		PrintErrorMessage(error, lexer, out);
    }
}

void RunCompiler(const char* file_name, bool noopt)
{
    ThrowLexerError = true;

    Lexer lexer(file_name);
    lexer.NextToken();
    Parser parser(lexer);
	try {
		TranslationUnit translation_unit = parser.ParseTranslationUnit();
		AsmProgram asm_program;
		translation_unit.Generate(asm_program);
		if (!noopt)
			asm_program.Optimize();
		std::string s(file_name);
		std::string::size_type i = s.rfind(".");
		if (i != s.npos)
			s.erase(i, s.size()-1);
		if (noopt)
			s += "_noopt";
		s += ".asm";
		std::ofstream fout(s.c_str());
		asm_program.Output(fout);
	}
	catch (CompilerError& error) {
		PrintErrorMessage(error, lexer, std::cout);
	}
}

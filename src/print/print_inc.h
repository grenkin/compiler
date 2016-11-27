#ifndef PRINT_INC_H_INCLUDED
#define PRINT_INC_H_INCLUDED

#include <iostream>
#include <string>

namespace {

    void PrintSpaces(int indent_level, std::ostream& out)
    {
        for (int i = 0; i < 2*indent_level; ++i)
            out << ' ';
    }

    void PrintOperator(OperatorT op, int indent_level, std::ostream& out)
    {
        const int OPERATORS_NUMBER = 39;
        const char* OPERATORS_STR[OPERATORS_NUMBER] = {
            "<<=", ">>=", "...", "++", "--", "->", "<<", ">>", "<=", ">=",
            "==", "!=", "&&", "||", "*=", "/=", "%=", "+=", "-=", "^=",
            "|=", "&=", ".", ",", ":", "&", "|", "^", "~", "!", "*", "/",
            "+", "-", ">", "<", "=", "%", "?"};
        PrintSpaces(indent_level, out);
        out << OPERATORS_STR[op] << '\n';
    }

    void PrintDelimiter(DelimiterT delim, int indent_level, std::ostream& out)
    {
        const int DELIMITERS_NUMBER = 7;
        const char* DELIMITERS_STR[DELIMITERS_NUMBER] = {
            "{", "}", "(", ")", "[", "]", ";"};
        PrintSpaces(indent_level, out);
        out << DELIMITERS_STR[delim] << '\n';
    }

    void PrintString(std::string s, int indent_level, std::ostream& out)
    {
        PrintSpaces(indent_level, out);
        out << s << '\n';
    }

	void PrintKeyword(IdentifierOrKeywordT keyword, std::ostream& out)
	{
		const int KEYWORDS_NUMBER = 33;
		const char* KEYWORDS_STR[KEYWORDS_NUMBER] = {
			"", "auto", "break", "case", "char", "const", "continue",
			"default", "do", "double", "else", "enum", "extern", "float",
			"for", "goto", "if", "int", "long", "register", "return",
			"short", "signed", "sizeof", "static", "struct", "switch",
			"typedef", "union", "unsigned", "void", "volatile", "while"
		};
		out << KEYWORDS_STR[keyword];
	}

}

#endif // PRINT_INC_H_INCLUDED

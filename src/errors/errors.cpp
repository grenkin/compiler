#include "errors.h"

bool ThrowLexerError = true;

CompilerError::CompilerError(std::string message, int line, int pos)
    : message(message), line(line), pos(pos)
{
}

LexerOrSyntaxError::LexerOrSyntaxError(std::string message, int line, int pos)
    : CompilerError(message, line, pos)
{
}

LexerError::LexerError(std::string message, int line, int pos, std::string text)
    : LexerOrSyntaxError(message, line, pos), text(text)
{
}

SyntaxError::SyntaxError(std::string message, int line, int pos)
    : LexerOrSyntaxError(message, line, pos)
{
}

IdRedeclarationError::IdRedeclarationError()
	: CompilerError("Identifier redeclaration", 0, 0)
{
}

TypesError::TypesError(std::string message, int line, int pos)
	: CompilerError(message, line, pos)
{
}

GeneratorError::GeneratorError(std::string message)
	: CompilerError(message, 0, 0)
{
}

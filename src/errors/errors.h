#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include <string>

enum CompilerErrorClass {
    COMPILER_ERROR_CLASS_LEXER,
    COMPILER_ERROR_CLASS_SYNTAX,
	COMPILER_ERROR_CLASS_ID_REDECL,
    COMPILER_ERROR_CLASS_TYPES,
    COMPILER_ERROR_CLASS_GENERATOR
};

class CompilerError {
protected:
    std::string message;
    int line, pos;
    CompilerError(std::string, int, int);
public:
    virtual ~CompilerError() {}
    virtual CompilerErrorClass ErrorClass() const = 0;
    std::string Message() { return message; }
    int Line() { return line; }
    int Pos() { return pos; }
};

class LexerOrSyntaxError : public CompilerError {
protected:
    LexerOrSyntaxError(std::string, int, int);
};

class LexerError : public LexerOrSyntaxError {
    std::string text;
public:
    LexerError(std::string, int, int, std::string);
    CompilerErrorClass ErrorClass() const {
        return COMPILER_ERROR_CLASS_LEXER; }
    std::string Text() { return text; }
};

class SyntaxError : public LexerOrSyntaxError {
public:
    SyntaxError(std::string, int, int);
    CompilerErrorClass ErrorClass() const {
        return COMPILER_ERROR_CLASS_SYNTAX; }
};

class IdRedeclarationError : public CompilerError {
public:
	IdRedeclarationError();
    CompilerErrorClass ErrorClass() const {
        return COMPILER_ERROR_CLASS_ID_REDECL; }
};

class TypesError : public CompilerError {
public:
    TypesError(std::string, int, int);
    CompilerErrorClass ErrorClass() const {
        return COMPILER_ERROR_CLASS_TYPES; }
};

class GeneratorError : public CompilerError {
public:
    GeneratorError(std::string);
    CompilerErrorClass ErrorClass() const {
        return COMPILER_ERROR_CLASS_GENERATOR; }
};

extern bool ThrowLexerError;

#endif // ERRORS_H_INCLUDED

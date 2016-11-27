#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "lexer_impl.h"
#include "..\errors\errors.h"

class Lexer;

class Token {
    friend class Lexer;
    static Token* CreateToken(TokenClass);
protected:
    virtual void CalcValue(LexerImplementation::
        FAStatesList&) = 0;
    std::string text;
    int line, pos;
public:
    virtual ~Token() {}
    virtual TokenClass Tok_cl() const = 0;
    const std::string& Text() const { return text; }
    int Line() const { return line; };
    int Pos() const { return pos; };
    virtual bool IsIdentifier() const { return false; }
    virtual bool IsKeyword(IdentifierOrKeywordT) const { return false; }
    virtual bool IsOperator(OperatorT) const { return false; }
    virtual bool IsDelimiter(DelimiterT) const { return false; }
};

class Token_begin_of_file : public Token {
    void CalcValue(LexerImplementation::FAStatesList&) {}
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_BEGIN_OF_FILE; }
};

class Token_end_of_file : public Token {
    void CalcValue(LexerImplementation::FAStatesList&) {}
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_END_OF_FILE; }
};

class Token_error : public Token {
    std::string value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_ERROR; }
    std::string Value() const { return value; }
};

class Token_int_const : public Token {
    friend class Lexer;
    int value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_INT_CONST; }
    int Value() const { return value; }
};

class Token_real_const : public Token {
    friend class Lexer;
    double value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_REAL_CONST; }
    double Value() const { return value; }
};

class Token_char_const : public Token {
    friend class Lexer;
    char value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_CHAR_CONST; }
    char Value() const { return value; }
};

class Token_string_const : public Token {
    friend class Lexer;
    std::string value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_STRING_CONST; }
    std::string Value() const { return value; }
};

class Token_ident_or_keyword : public Token {
    friend class Lexer;
    IdentifierOrKeywordT value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_IDENTIFIER_OR_KEYWORD; }
    IdentifierOrKeywordT Value() const { return value; }
    bool IsIdentifier() const { return (value == IDENT_OR_KEYWORD_IDENT); }
    bool IsKeyword(IdentifierOrKeywordT id_or_kw) const { return (value == id_or_kw); }
};

class Token_operator : public Token {
    friend class Lexer;
    OperatorT value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_OPERATOR; }
    OperatorT Value() const { return value; }
    bool IsOperator(OperatorT op) const { return (value == op); }
};

class Token_delimiter : public Token {
    friend class Lexer;
    DelimiterT value;
    void CalcValue(LexerImplementation::FAStatesList&);
public:
    TokenClass Tok_cl() const { return TOKEN_CLASS_DELIMITER; }
    DelimiterT Value() const { return value; }
    bool IsDelimiter(DelimiterT delim) const { return (value == delim); }
};

class Lexer {
    std::ifstream input_stream;
    LexerImplementation::FiniteAutomaton automaton;
    Token* token;
public:
    Lexer(const char*);
    ~Lexer();
    Token* GetToken();
    void NextToken();
};

#endif // LEXER_H_INCLUDED

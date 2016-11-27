#include "lexer.h"

using namespace LexerImplementation;

Token* Token::CreateToken(TokenClass tok_cl)
{
    switch (tok_cl) {
        case TOKEN_CLASS_BEGIN_OF_FILE: return new Token_begin_of_file; break;
        case TOKEN_CLASS_END_OF_FILE: return new Token_end_of_file; break;
        case TOKEN_CLASS_ERROR: return new Token_error; break;
        case TOKEN_CLASS_INT_CONST: return new Token_int_const; break;
        case TOKEN_CLASS_REAL_CONST: return new Token_real_const; break;
        case TOKEN_CLASS_CHAR_CONST: return new Token_char_const; break;
        case TOKEN_CLASS_STRING_CONST: return new Token_string_const; break;
        case TOKEN_CLASS_IDENTIFIER_OR_KEYWORD: return new Token_ident_or_keyword; break;
        case TOKEN_CLASS_OPERATOR: return new Token_operator; break;
        case TOKEN_CLASS_DELIMITER: return new Token_delimiter; break;
    }
}

Lexer::Lexer(const char* file_name)
    : input_stream(file_name), automaton(input_stream),
    token(Token::CreateToken(TOKEN_CLASS_BEGIN_OF_FILE))
{
}

Lexer::~Lexer()
{
    delete token;
}

Token* Lexer::GetToken()
{
    return token;
}

void Lexer::NextToken()
{
    FAStatesList st_list = automaton.StartAutomaton();
    Nonterminal* last_state = st_list.back().state;
    TokenClass token_class = (last_state->Type() == NONTERM_TYPE_TOKEN) ?
        static_cast<Nonterminal_token*>(last_state)->Tok_cl()
        : TOKEN_CLASS_ERROR;
    delete token;
    token = Token::CreateToken(token_class);
    FAStatesList::const_iterator last = (token_class == TOKEN_CLASS_ERROR) ?
        st_list.end() : --st_list.end();
    for (FAStatesList::const_iterator i = st_list.begin(); i != last; ++i)
        token->text += i->character;
    token->line = automaton.TokenStartLine();
    token->pos = automaton.TokenStartPos();
    token->CalcValue(st_list);

    if (ThrowLexerError && token_class == TOKEN_CLASS_ERROR)
        throw LexerError(static_cast<Token_error*>(token)->Value(),
            token->line, token->pos, token->text);
}

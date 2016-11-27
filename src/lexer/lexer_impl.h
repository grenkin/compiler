#ifndef LEXER_IMPL_H_INCLUDED
#define LEXER_IMPL_H_INCLUDED

#include <fstream>

#include "lexer_grammar.h"

namespace LexerImplementation {

    struct FAStatesListElement {
        Nonterminal* state;
        char character;
        FAStatesListElement(Nonterminal*, char);
    };

    typedef std::vector<FAStatesListElement> FAStatesList;

    class FiniteAutomaton {
        std::ifstream* input_stream;
        RegularGrammar grammar;
        int line, pos; //строка и позици¤ последнего прочитанного из потока символа
        int token_start_line, token_start_pos;
    public:
        FiniteAutomaton(std::ifstream&);
        FAStatesList StartAutomaton();
        int TokenStartLine() const { return token_start_line; }
        int TokenStartPos() const { return token_start_pos; }
    };

} //namespace

#endif // LEXER_IMPL_H_INCLUDED

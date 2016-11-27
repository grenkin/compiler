#ifndef LEXER_GRAMMAR_IMPL_H_INCLUDED
#define LEXER_GRAMMAR_IMPL_H_INCLUDED

#include <vector>
#include <string>
#include "lexer_types.h"

namespace LexerImplementation {

    enum NonterminalType {
        NONTERM_TYPE_WHITE_SPACE,
        NONTERM_TYPE_USUAL,
        NONTERM_TYPE_TOKEN,
        NONTERM_TYPE_ERROR
    };

    class SetOfTerminals {
        friend class Nonterminal;
        std::vector<char> t_list;
    public:
        SetOfTerminals();
        SetOfTerminals(char);
        void Add(char);
    };

    class Nonterminal;

    class Nonterminal_amp_SetOfTerminals {
        friend class Nonterminal;
        Nonterminal* nt;
        SetOfTerminals set_of_t;
    public:
        Nonterminal_amp_SetOfTerminals(Nonterminal*, SetOfTerminals);
    };

    typedef std::vector<Nonterminal_amp_SetOfTerminals> NtTList;

    class RightPartOfSubstitutionRule {
        friend class Nonterminal;
        friend RightPartOfSubstitutionRule operator|(RightPartOfSubstitutionRule,
            Nonterminal_amp_SetOfTerminals);
        NtTList nt_t_list;
    public:
        RightPartOfSubstitutionRule(SetOfTerminals);
        RightPartOfSubstitutionRule(char);
        RightPartOfSubstitutionRule(Nonterminal_amp_SetOfTerminals);
    };

    class Nonterminal {
    protected:
        Nonterminal* m[256];
        Nonterminal();
    public:
        virtual ~Nonterminal() {}
        virtual NonterminalType Type() const = 0;
        Nonterminal* Switch(char ch) { return m[ch+128]; }
        Nonterminal_amp_SetOfTerminals operator&(SetOfTerminals);
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_white_space : public Nonterminal {
    public:
        NonterminalType Type() const { return NONTERM_TYPE_WHITE_SPACE; }
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_usual : public Nonterminal {
    public:
        NonterminalType Type() const { return NONTERM_TYPE_USUAL; }
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_usual_operator : public Nonterminal_usual {
        OperatorT op;
    public:
        Nonterminal_usual_operator(OperatorT);
        OperatorT Op() { return op; }
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_usual_delimiter : public Nonterminal_usual {
        DelimiterT delim;
    public:
        Nonterminal_usual_delimiter(DelimiterT);
        DelimiterT Delim() { return delim; }
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_token : public Nonterminal {
        TokenClass tok_cl;
    public:
        Nonterminal_token(TokenClass);
        NonterminalType Type() const { return NONTERM_TYPE_TOKEN; }
        TokenClass Tok_cl() const { return tok_cl; }
        void operator=(RightPartOfSubstitutionRule);
    };

    class Nonterminal_error : public Nonterminal {
        std::string message;
    public:
        Nonterminal_error(std::string);
        NonterminalType Type() const { return NONTERM_TYPE_ERROR; }
        std::string Message() const { return message; }
        void operator=(RightPartOfSubstitutionRule);
    };

    extern Nonterminal_usual initial_state;
    extern Nonterminal_error default_error;

    RightPartOfSubstitutionRule operator|(RightPartOfSubstitutionRule,
        Nonterminal_amp_SetOfTerminals);
    RightPartOfSubstitutionRule operator|(RightPartOfSubstitutionRule,
        SetOfTerminals);

} //namespace

#endif // LEXER_GRAMMAR_IMPL_H_INCLUDED

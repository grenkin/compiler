#include "lexer_grammar_impl.h"

using namespace LexerImplementation;

namespace LexerImplementation {
    Nonterminal_usual initial_state;
    Nonterminal_error default_error("Default error");
}

SetOfTerminals::SetOfTerminals()
{
}

SetOfTerminals::SetOfTerminals(char ch)
{
    Add(ch);
}

void SetOfTerminals::Add(char ch)
{
    t_list.push_back(ch);
}

Nonterminal_amp_SetOfTerminals::Nonterminal_amp_SetOfTerminals(Nonterminal* nt, SetOfTerminals set_of_t)
    : nt(nt), set_of_t(set_of_t)
{
}

RightPartOfSubstitutionRule::RightPartOfSubstitutionRule(SetOfTerminals set_of_t)
{
    nt_t_list.push_back(Nonterminal_amp_SetOfTerminals(&initial_state, set_of_t));
}

RightPartOfSubstitutionRule::RightPartOfSubstitutionRule(char ch)
{
    nt_t_list.push_back(Nonterminal_amp_SetOfTerminals(&initial_state, ch));
}

RightPartOfSubstitutionRule::RightPartOfSubstitutionRule(Nonterminal_amp_SetOfTerminals nt_t)
{
    nt_t_list.push_back(nt_t);
}

Nonterminal::Nonterminal()
{
    for (int i = 0; i < 256; ++i)
        m[i] = &default_error;
}

Nonterminal_amp_SetOfTerminals Nonterminal::operator&(SetOfTerminals set_of_t)
{
    return Nonterminal_amp_SetOfTerminals(this, set_of_t);
}

void Nonterminal::operator=(RightPartOfSubstitutionRule right_part)
{
    for (NtTList::const_iterator i = right_part.nt_t_list.begin();
    i != right_part.nt_t_list.end(); ++i) {
        for (std::vector<char>::const_iterator j = i->set_of_t.t_list.begin();
        j != i->set_of_t.t_list.end(); ++j)
            i->nt->m[*j+128] = this;
    }
}

void Nonterminal_white_space::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal::operator=(right_part);
}

void Nonterminal_usual::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal::operator=(right_part);
}

Nonterminal_usual_operator::Nonterminal_usual_operator(OperatorT op)
    : op(op)
{
}

void Nonterminal_usual_operator::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal_usual::operator=(right_part);
}

Nonterminal_usual_delimiter::Nonterminal_usual_delimiter(DelimiterT delim)
    : delim(delim)
{
}

void Nonterminal_usual_delimiter::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal_usual::operator=(right_part);
}

Nonterminal_token::Nonterminal_token(TokenClass tok_cl)
    : tok_cl(tok_cl)
{
}

void Nonterminal_token::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal::operator=(right_part);
}

Nonterminal_error::Nonterminal_error(std::string message)
    : message(message)
{
}

void Nonterminal_error::operator=(RightPartOfSubstitutionRule right_part)
{
    Nonterminal::operator=(right_part);
}

RightPartOfSubstitutionRule LexerImplementation::operator|(RightPartOfSubstitutionRule right_part,
    Nonterminal_amp_SetOfTerminals nt_t)
{
    right_part.nt_t_list.push_back(nt_t);
    return right_part;
}

RightPartOfSubstitutionRule LexerImplementation::operator|(RightPartOfSubstitutionRule right_part,
    SetOfTerminals set_of_t)
{
    return right_part | Nonterminal_amp_SetOfTerminals(&initial_state, set_of_t);
}

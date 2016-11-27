#include "lexer_impl.h"

using namespace LexerImplementation;

extern Nonterminal_usual initial_state;
extern Nonterminal_error default_error;

FAStatesListElement::FAStatesListElement(Nonterminal* state, char character)
    : state(state), character(character)
{
}

FiniteAutomaton::FiniteAutomaton(std::ifstream& input_stream)
    : input_stream(&input_stream), line(1), pos(0)
{
}

FAStatesList FiniteAutomaton::StartAutomaton()
{
    FAStatesList states_list;
    Nonterminal* current_state = &initial_state;
    token_start_line = line; token_start_pos = pos+1;
    //Комментарий к последней инструкции
    //  Не нужно рассматривать отдельно частный случай, когда
    //  первым считанным из входного потока символом будет перевод строки,
    //  так как этот символ не принадлежит лексеме.
    char ch;
    int prev_line, prev_pos;
    while (!(current_state->Type() == NONTERM_TYPE_ERROR ||
        current_state->Type() == NONTERM_TYPE_TOKEN)) {
        ch = input_stream->get();
        prev_line = line; prev_pos = pos;
        (ch == '\n') ? ++line, pos = 0 : ++pos;
        current_state = current_state->Switch(ch);
        states_list.push_back(FAStatesListElement(
            current_state, ch));
        if (current_state->Type() == NONTERM_TYPE_WHITE_SPACE) {
            states_list.clear();
            current_state = &initial_state;
            token_start_line = line; token_start_pos = pos+1;
        }
    }
    input_stream->putback(ch);
    line = prev_line; pos = prev_pos;
    return states_list;
}

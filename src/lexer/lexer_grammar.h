#ifndef LEXER_GRAMMAR_H_INCLUDED
#define LEXER_GRAMMAR_H_INCLUDED

#include "lexer_grammar_impl.h"

namespace LexerImplementation {

    struct RegularGrammar {
        static Nonterminal_white_space white_space;
        static Nonterminal_token token_end_of_file, token_int_const,
            token_real_const, token_char_const, token_string_const,
            token_ident_or_keyword, token_operator, token_delimiter;
        static Nonterminal_usual int_dec_const, zero, int_oct_const,
            int_hex_const, pref_hex_const, real_const_without_e,
            real_const, zero_digits, real_const_e, real_const_e_sign,
            comment_star, comment, comment_slash, identifier,
            char_const, char_const_escape_seq, char_const_oct_code,
            char_const_hex_code, s_quote_back_slash_char,
            s_quote_back_slash_1_oct_digit, s_quote_back_slash_2_oct_digits,
            s_quote_back_slash_3_oct_digits, s_quote_back_slash_x_hex_digits,
            s_quote_char, single_quote, s_quote_back_slash, s_quote_back_slash_x,
            string_const, double_quote_chars,
            d_quote_chars_back_slash_char,
            d_quote_chars_back_slash_1_oct_digit,
            d_quote_chars_back_slash_2_oct_digits,
            d_quote_chars_back_slash_3_oct_digits,
            d_quote_chars_back_slash_x_hex_digits, d_quote_chars_back_slash,
            d_quote_chars_back_slash_x, two_points;
        static Nonterminal_usual_delimiter left_brace, right_brace, left_round_bracket,
            right_round_bracket, left_square_bracket, right_square_bracket, semicolon;
        static Nonterminal_usual_operator less_less_equal, more_more_equal, ellipsis,
            plus_plus, minus_minus, arrow, less_less, more_more,
            less_equal, more_equal, equal_equal, excl_mark_equal,
            amp_amp, vert_line_vert_line, star_equal, slash_equal,
            percent_equal, plus_equal, minus_equal, cover_equal,
            vert_line_equal, amp_equal,
            point, comma, colon, amp, vert_line, cover, squiggle,
            excl_mark, star, slash, plus, minus,
            more, less, equal, percent, quest_mark;
        static Nonterminal_error nested_comm_error;
        RegularGrammar();
    };

} //namespace

#endif // LEXER_GRAMMAR_H_INCLUDED

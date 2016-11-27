#include "lexer_grammar.h"

namespace LexerImplementation {

    Nonterminal_white_space RegularGrammar::white_space;

    Nonterminal_token
        RegularGrammar::token_end_of_file(TOKEN_CLASS_END_OF_FILE),
        RegularGrammar::token_int_const(TOKEN_CLASS_INT_CONST),
        RegularGrammar::token_real_const(TOKEN_CLASS_REAL_CONST),
        RegularGrammar::token_char_const(TOKEN_CLASS_CHAR_CONST),
        RegularGrammar::token_string_const(TOKEN_CLASS_STRING_CONST),
        RegularGrammar::token_ident_or_keyword(TOKEN_CLASS_IDENTIFIER_OR_KEYWORD),
        RegularGrammar::token_operator(TOKEN_CLASS_OPERATOR),
        RegularGrammar::token_delimiter(TOKEN_CLASS_DELIMITER);

    Nonterminal_usual RegularGrammar::int_dec_const, RegularGrammar::zero,
        RegularGrammar::int_oct_const, RegularGrammar::int_hex_const,
        RegularGrammar::pref_hex_const, RegularGrammar::real_const_without_e,
        RegularGrammar::real_const, RegularGrammar::zero_digits,
        RegularGrammar::real_const_e,
        RegularGrammar::real_const_e_sign,
        RegularGrammar::comment_star,
        RegularGrammar::comment,
        RegularGrammar::comment_slash,
        RegularGrammar::identifier, RegularGrammar::char_const,
        RegularGrammar::char_const_escape_seq,
        RegularGrammar::char_const_oct_code,
        RegularGrammar::char_const_hex_code,
        RegularGrammar::s_quote_back_slash_char,
        RegularGrammar::s_quote_back_slash_1_oct_digit,
        RegularGrammar::s_quote_back_slash_2_oct_digits,
        RegularGrammar::s_quote_back_slash_3_oct_digits,
        RegularGrammar::s_quote_back_slash_x_hex_digits,
        RegularGrammar::s_quote_char, RegularGrammar::single_quote,
        RegularGrammar::s_quote_back_slash, RegularGrammar::s_quote_back_slash_x,
        RegularGrammar::string_const, RegularGrammar::double_quote_chars,
        RegularGrammar::d_quote_chars_back_slash_char,
        RegularGrammar::d_quote_chars_back_slash_1_oct_digit,
        RegularGrammar::d_quote_chars_back_slash_2_oct_digits,
        RegularGrammar::d_quote_chars_back_slash_3_oct_digits,
        RegularGrammar::d_quote_chars_back_slash_x_hex_digits,
        RegularGrammar::d_quote_chars_back_slash,
        RegularGrammar::d_quote_chars_back_slash_x,
        RegularGrammar::two_points;

    Nonterminal_usual_delimiter RegularGrammar::left_brace(DELIM_LEFT_BRACE),
        RegularGrammar::right_brace(DELIM_RIGHT_BRACE),
        RegularGrammar::left_round_bracket(DELIM_LEFT_ROUND_BRACKET),
        RegularGrammar::right_round_bracket(DELIM_RIGHT_ROUND_BRACKET),
        RegularGrammar::left_square_bracket(DELIM_LEFT_SQUARE_BRACKET),
        RegularGrammar::right_square_bracket(DELIM_RIGHT_SQUARE_BRACKET),
        RegularGrammar::semicolon(DELIM_SEMICOLON);

    Nonterminal_usual_operator RegularGrammar::less_less_equal(OP_LESS_LESS_EQUAL),
        RegularGrammar::more_more_equal(OP_MORE_MORE_EQUAL),
        RegularGrammar::ellipsis(OP_ELLIPSIS),
        RegularGrammar::plus_plus(OP_PLUS_PLUS),
        RegularGrammar::minus_minus(OP_MINUS_MINUS),
        RegularGrammar::arrow(OP_ARROW),
        RegularGrammar::less_less(OP_LESS_LESS),
        RegularGrammar::more_more(OP_MORE_MORE),
        RegularGrammar::less_equal(OP_LESS_EQUAL),
        RegularGrammar::more_equal(OP_MORE_EQUAL),
        RegularGrammar::equal_equal(OP_EQUAL_EQUAL),
        RegularGrammar::excl_mark_equal(OP_EXCL_MARK_EQUAL),
        RegularGrammar::amp_amp(OP_AMP_AMP),
        RegularGrammar::vert_line_vert_line(OP_VERT_LINE_VERT_LINE),
        RegularGrammar::star_equal(OP_STAR_EQUAL),
        RegularGrammar::slash_equal(OP_SLASH_EQUAL),
        RegularGrammar::percent_equal(OP_PERCENT_EQUAL),
        RegularGrammar::plus_equal(OP_PLUS_EQUAL),
        RegularGrammar::minus_equal(OP_MINUS_EQUAL),
        RegularGrammar::cover_equal(OP_COVER_EQUAL),
        RegularGrammar::vert_line_equal(OP_VERT_LINE_EQUAL),
        RegularGrammar::amp_equal(OP_AMP_EQUAL),
        RegularGrammar::point(OP_POINT),
        RegularGrammar::comma(OP_COMMA),
        RegularGrammar::colon(OP_COLON),
        RegularGrammar::amp(OP_AMP),
        RegularGrammar::vert_line(OP_VERT_LINE),
        RegularGrammar::cover(OP_COVER),
        RegularGrammar::squiggle(OP_SQUIGGLE),
        RegularGrammar::excl_mark(OP_EXCL_MARK),
        RegularGrammar::star(OP_STAR),
        RegularGrammar::slash(OP_SLASH),
        RegularGrammar::plus(OP_PLUS),
        RegularGrammar::minus(OP_MINUS),
        RegularGrammar::more(OP_MORE),
        RegularGrammar::less(OP_LESS),
        RegularGrammar::equal(OP_EQUAL),
        RegularGrammar::percent(OP_PERCENT),
        RegularGrammar::quest_mark(OP_QUEST_MARK);

    Nonterminal_error RegularGrammar::nested_comm_error("Nested comments");

}

using namespace LexerImplementation;

static bool is_letter(char);
static bool is_digit(char);
static bool is_oct_digit(char);
static bool is_hex_digit(char);

RegularGrammar::RegularGrammar()
{
    SetOfTerminals t_white_space_char;
    const int WS_CHARS_NUMBER = 7;
    const char ws_chars[WS_CHARS_NUMBER] = {' ', '\t', '\v', '\n', '\r', '\f', '\b'};
    for (int i = 0; i < WS_CHARS_NUMBER; ++i)
        t_white_space_char.Add(ws_chars[i]);
    SetOfTerminals t_not_letter_and_not_digit,
        t_not_letter_and_not_digit_and_not_point, t_not_digit_and_not_point;
    for (int i = 0; i < 256; ++i) {
        char ch = i;
        if (!is_letter(ch) && !is_digit(ch)) {
            t_not_letter_and_not_digit.Add(ch);
            if (ch != '.')
                t_not_letter_and_not_digit_and_not_point.Add(ch);
        }
        if (!is_digit(ch) && ch != '.')
            t_not_digit_and_not_point.Add(ch);
    }
    SetOfTerminals t_any_char, t_letter, t_digit, t_oct_digit, t_nonzero_digit,
        t_hex_digit;
    for (int i = 0; i < 256; ++i) {
        char ch = i;
        t_any_char.Add(ch);
        if (is_letter(ch))
            t_letter.Add(ch);
        if (is_digit(ch)) {
            t_digit.Add(ch);
            if (ch != '0')
                t_nonzero_digit.Add(ch);
        }
        if (is_oct_digit(ch))
            t_oct_digit.Add(ch);
        if (is_hex_digit(ch))
            t_hex_digit.Add(ch);
    }
    SetOfTerminals t_not_star, t_not_star_and_not_eof,
        t_not_star_and_not_slash, t_not_star_and_not_slash_and_not_eof,
        t_not_double_quote, t_not_equal, t_not_amp_and_not_equal,
        t_not_vert_line_and_not_equal, t_not_star_and_not_equal,
        t_not_plus_and_not_equal, t_not_minus_and_not_more_and_not_equal,
        t_not_more_and_not_equal, t_not_less_and_not_equal;
    for (int i = 0; i < 256; ++i) {
        char ch = i;
        if (ch != '*') {
            t_not_star.Add(ch);
            if (ch != EOF)
                t_not_star_and_not_eof.Add(ch);
        }
        if (ch != '*' && ch != '/') {
            t_not_star_and_not_slash.Add(ch);
            if (ch != EOF)
                t_not_star_and_not_slash_and_not_eof.Add(ch);
        }
        if (ch != '\"')
            t_not_double_quote.Add(ch);
        if (ch != '=')
            t_not_equal.Add(ch);
        if (ch != '&' && ch != '=')
            t_not_amp_and_not_equal.Add(ch);
        if (ch != '|' && ch != '=')
            t_not_vert_line_and_not_equal.Add(ch);
        if (ch != '*' && ch != '=')
            t_not_star_and_not_equal.Add(ch);
        if (ch != '+' && ch != '=')
            t_not_plus_and_not_equal.Add(ch);
        if (ch != '-' && ch != '>' && ch != '=')
            t_not_minus_and_not_more_and_not_equal.Add(ch);
        if (ch != '>' && ch != '=')
            t_not_more_and_not_equal.Add(ch);
        if (ch != '<' && ch != '=')
            t_not_less_and_not_equal.Add(ch);
    }
    SetOfTerminals t_not_back_slash_and_not_new_line_and_not_s_quote_and_not_eof,
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_eof,
        t_not_oct_digit_and_not_x_and_not_new_line_and_not_eof,
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_oct_digit_and_not_eof,
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_hex_digit_and_not_eof;
    for (int i = 0; i < 256; ++i) {
        char ch = i;
        if (ch != '\\' && ch != '\n' && ch != '\'' && ch != EOF)
            t_not_back_slash_and_not_new_line_and_not_s_quote_and_not_eof.Add(ch);
        if (ch != '\\' && ch != '\n' && ch != '\"' && ch != EOF)
            t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_eof.Add(ch);
        if (!is_oct_digit(ch) && ch != 'x' && ch != '\n' && ch != EOF)
            t_not_oct_digit_and_not_x_and_not_new_line_and_not_eof.Add(ch);
        if (ch != '\\' && ch != '\n' && ch != '\"' && !is_oct_digit(ch) && ch != EOF)
            t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_oct_digit_and_not_eof.Add(ch);
        if (ch != '\\' && ch != '\n' && ch != '\"' && !is_hex_digit(ch) && ch != EOF)
            t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_hex_digit_and_not_eof.Add(ch);
    }

    token_end_of_file = EOF;
    white_space = t_white_space_char;
    token_int_const = int_dec_const&t_not_letter_and_not_digit_and_not_point |
        zero&t_not_letter_and_not_digit_and_not_point |
        int_oct_const&t_not_letter_and_not_digit_and_not_point |
        int_hex_const&t_not_letter_and_not_digit;
    int_dec_const = t_nonzero_digit | int_dec_const&t_digit;
    zero = '0';
    int_oct_const = zero&t_oct_digit | int_oct_const&t_oct_digit;
    int_hex_const = pref_hex_const&t_hex_digit | int_hex_const&t_hex_digit;
    pref_hex_const = zero&'x' | zero&'X';

    token_real_const = real_const_without_e&t_not_letter_and_not_digit |
        real_const&t_not_letter_and_not_digit;
    real_const_without_e = int_dec_const&'.' | int_oct_const&'.' | zero&'.' |
        zero_digits&'.' | point&t_digit | real_const_without_e&t_digit;
    real_const = real_const_e&t_digit | real_const_e_sign&t_digit |
        real_const&t_digit;
    real_const_e = real_const_without_e&'e' | real_const_without_e&'E';
    real_const_e_sign = real_const_e&'+' | real_const_e&'-';
    point = '.';
    zero_digits = zero&'8' | zero&'9' | int_oct_const&'8' | int_oct_const&'9' |
        zero_digits&t_digit;

    white_space = comment_star&'/';
    comment_star = comment&'*' | comment_star&'*';
    comment = slash&'*' | comment&t_not_star_and_not_slash_and_not_eof |
        comment_star&t_not_star_and_not_slash_and_not_eof |
        comment_slash&t_not_star_and_not_eof;
    slash = '/';
    token_operator = slash&t_not_star;
    nested_comm_error = comment_slash&'*';
    comment_slash = comment&'/';

    token_ident_or_keyword = identifier&t_not_letter_and_not_digit;
    identifier = t_letter | identifier&t_letter | identifier&t_digit;

    token_char_const = char_const&t_any_char |
        char_const_escape_seq&t_any_char |
        char_const_oct_code&t_any_char |
        char_const_hex_code&t_any_char;
    char_const = s_quote_char&'\'';
    char_const_escape_seq = s_quote_back_slash_char&'\'';
    char_const_oct_code = s_quote_back_slash_1_oct_digit&'\'' |
        s_quote_back_slash_2_oct_digits&'\'' |
        s_quote_back_slash_3_oct_digits&'\'';
    char_const_hex_code = s_quote_back_slash_x_hex_digits&'\'';
    s_quote_char = single_quote&t_not_back_slash_and_not_new_line_and_not_s_quote_and_not_eof;
    s_quote_back_slash_char = s_quote_back_slash&t_not_oct_digit_and_not_x_and_not_new_line_and_not_eof;
    s_quote_back_slash_3_oct_digits = s_quote_back_slash_2_oct_digits&t_oct_digit;
    s_quote_back_slash_2_oct_digits = s_quote_back_slash_1_oct_digit&t_oct_digit;
    s_quote_back_slash_1_oct_digit = s_quote_back_slash&t_oct_digit;
    s_quote_back_slash_x_hex_digits = s_quote_back_slash_x&t_hex_digit |
        s_quote_back_slash_x_hex_digits&t_hex_digit;
    s_quote_back_slash_x = s_quote_back_slash&'x';
    s_quote_back_slash = single_quote&'\\';
    single_quote = '\'';

    token_string_const = string_const&t_not_double_quote;
    string_const = double_quote_chars&'\"' | d_quote_chars_back_slash_char&'\"' |
        d_quote_chars_back_slash_1_oct_digit&'\"' |
        d_quote_chars_back_slash_2_oct_digits&'\"' |
        d_quote_chars_back_slash_3_oct_digits&'\"' |
        d_quote_chars_back_slash_x_hex_digits&'\"';
    double_quote_chars = '\"' |
        double_quote_chars&t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_eof |
        d_quote_chars_back_slash_char&t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_eof |
        d_quote_chars_back_slash_1_oct_digit&
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_oct_digit_and_not_eof |
        d_quote_chars_back_slash_2_oct_digits&
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_oct_digit_and_not_eof |
        d_quote_chars_back_slash_3_oct_digits&
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_oct_digit_and_not_eof |
        d_quote_chars_back_slash_x_hex_digits&
        t_not_back_slash_and_not_new_line_and_not_d_quote_and_not_hex_digit_and_not_eof |
        string_const&'\"';
    d_quote_chars_back_slash = double_quote_chars&'\\' |
        d_quote_chars_back_slash_char&'\\' |
        d_quote_chars_back_slash_1_oct_digit&'\\' |
        d_quote_chars_back_slash_2_oct_digits&'\\' |
        d_quote_chars_back_slash_3_oct_digits&'\\' |
        d_quote_chars_back_slash_x_hex_digits&'\\';
    d_quote_chars_back_slash_char = d_quote_chars_back_slash&
        t_not_oct_digit_and_not_x_and_not_new_line_and_not_eof;
    d_quote_chars_back_slash_1_oct_digit = d_quote_chars_back_slash&t_oct_digit;
    d_quote_chars_back_slash_2_oct_digits = d_quote_chars_back_slash_1_oct_digit&
        t_oct_digit;
    d_quote_chars_back_slash_3_oct_digits = d_quote_chars_back_slash_2_oct_digits&
        t_oct_digit;
    d_quote_chars_back_slash_x = d_quote_chars_back_slash&'x';
    d_quote_chars_back_slash_x_hex_digits = d_quote_chars_back_slash_x&t_hex_digit |
        d_quote_chars_back_slash_x_hex_digits&t_hex_digit;

    token_delimiter =
        left_brace&t_any_char | right_brace&t_any_char |
        left_round_bracket&t_any_char | right_round_bracket&t_any_char |
        left_square_bracket&t_any_char | right_square_bracket&t_any_char |
        semicolon&t_any_char;
    left_brace = '{'; right_brace = '}';
    left_round_bracket = '('; right_round_bracket = ')';
    left_square_bracket = '['; right_square_bracket = ']';
    semicolon = ';';

    token_operator =
        less_less_equal&t_any_char | more_more_equal&t_any_char |
        ellipsis&t_any_char;
    token_operator =
        plus_plus&t_any_char | minus_minus&t_any_char |
        arrow&t_any_char |
        less_less&t_not_equal | more_more&t_not_equal |
        less_equal&t_any_char | more_equal&t_any_char |
        equal_equal&t_any_char | excl_mark_equal&t_any_char |
        amp_amp&t_any_char | vert_line_vert_line&t_any_char |
        star_equal&t_any_char | slash_equal&t_any_char |
        percent_equal&t_any_char | plus_equal&t_any_char |
        minus_equal&t_any_char | cover_equal&t_any_char |
        vert_line_equal&t_any_char | amp_equal&t_any_char;
    token_operator =
        point&t_not_digit_and_not_point | comma&t_any_char |
        colon&t_any_char |
        amp&t_not_amp_and_not_equal | vert_line&t_not_vert_line_and_not_equal |
        cover&t_not_equal | squiggle&t_any_char | excl_mark&t_not_equal |
        star&t_not_equal | slash&t_not_star_and_not_equal |
        plus&t_not_plus_and_not_equal | minus&t_not_minus_and_not_more_and_not_equal |
        more&t_not_more_and_not_equal | less&t_not_less_and_not_equal |
        equal&t_not_equal | percent&t_not_equal | quest_mark&t_any_char;
    less_less_equal = less_less&'=';
    more_more_equal = more_more&'=';
    ellipsis = two_points&'.';
    two_points = point&'.';
    plus_plus = plus&'+';
    minus_minus = minus&'-';
    arrow = minus&'>';
    less_less = less&'<';
    more_more = more&'>';
    less_equal = less&'=';
    more_equal = more&'=';
    equal_equal = equal&'=';
    excl_mark_equal = excl_mark&'=';
    amp_amp = amp&'&';
    vert_line_vert_line = vert_line&'|';
    star_equal = star&'=';
    slash_equal = slash&'=';
    percent_equal = percent&'=';
    plus_equal = plus&'=';
    minus_equal = minus&'=';
    cover_equal = cover&'=';
    vert_line_equal = vert_line&'=';
    amp_equal = amp&'=';
    comma = ',';
    colon = ':';
    amp = '&';
    vert_line = '|';
    cover = '^';
    squiggle = '~';
    excl_mark = '!';
    star = '*';
    plus = '+';
    minus = '-';
    more = '>';
    less = '<';
    equal = '=';
    percent = '%';
    quest_mark = '?';
}

static bool is_letter(char ch)
{
    return (ch == '_' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

static bool is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

static bool is_oct_digit(char ch)
{
    return (is_digit(ch) && (ch != '8' && ch != '9'));
}

static bool is_hex_digit(char ch)
{
    return (is_digit(ch) || ch >= 'a' && ch <= 'f' || ch >= 'A' && ch <= 'F');
}

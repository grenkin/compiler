    float_const_e_sign = float_const_e&'+' | float_const_e&'-';
    point = '.';
    zero_digits = zero&'8' | zero&'9' | int_oct_const&'8' | int_oct_const&'9' |
        zero_digits&t_digit;

    white_space = comment_star&'/';
    comment_star = comment&'*';
    comment = slash&'*' | comment&t_not_star_and_not_slash |
        comment_star&t_not_slash | comment_slash&t_not_star;
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
    s_quote_char = single_quote&t_not_back_slash_and_not_new_line_and_not_s_quote;
    s_quote_back_slash_char = s_quote_back_slash&t_not_oct_digit_and_not_x_and_not_new_line;
    s_quote_back_slash_3_oct_digits = s_quote_back_slash_2_oct_digits&t_oct_digit;
    s_quote_back_slash_2_oct_digits = s_quote_back_slash_1_oct_digit&t_oct_digit;
    s_quote_back_slash_1_oct_digit = s_quote_back_slash&t_oct_digit;
    s_quote_back_slash_x_hex_digits = s_quote_back_slash_x&t_hex_digit |
        s_quote_back_slash_x_hex_digits&t_hex_digit;
    s_quote_back_slash_x = s_quote_back_slash&'x';
    s_quote_back_slash = single_quote&'\\';
    single_quote = '\'';

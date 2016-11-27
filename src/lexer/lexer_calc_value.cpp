#include "lexer.h"

using namespace LexerImplementation;

typedef RegularGrammar RG;

namespace {

    int digit(char ch)
    {
        return ch-'0';
    }

    int hex_digit(char ch)
    {
        if (ch >= '0' && ch <= '9')
            return ch-'0';
        else if (ch >= 'a' && ch <= 'z')
            return ch-'a'+10;
        else
            return ch-'A'+10;
    }

    char escape_char(char ch)
    {
        const int ESCAPE_CHARS_NUMBER = 11;
        const char ESCAPE_CHARS[ESCAPE_CHARS_NUMBER] = {
                'n', 't', 'v', 'b', 'r', 'f', 'a', '\\', '?', '\'', '\"'};
        const char ESCAPE_CHARS_VALUES[ESCAPE_CHARS_NUMBER] = {
                '\n', '\t', '\v', '\b', '\r', '\f', '\a', '\\', '?', '\'', '\"'};
        for (int i = 0; i < ESCAPE_CHARS_NUMBER; ++i) {
            if (ESCAPE_CHARS[i] == ch)
                return ESCAPE_CHARS_VALUES[i];
        }
        return '\0';
    };

}

void Token_error::CalcValue(FAStatesList& list)
{
    value = static_cast<Nonterminal_error*>(list.back().state)->Message();
}

void Token_int_const::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_int_const
    FAStatesList::reverse_iterator i = ++list.rbegin();
    if (i->state == &RG::int_dec_const) {
        int res = 0, z = 1;
        while (i != list.rend()) {
            res += (digit(i->character))*z; z *= 10;
            ++i;
        }
        value = res;
    }
    else if (i->state == &RG::zero)
        value = 0;
    else if (i->state == &RG::int_oct_const) {
        int res = 0, z = 1;
        while (i->state != &RG::zero) {
            res += digit(i->character)*z; z *= 8;
            ++i;
        }
        value = res;
    }
    else if (i->state == &RG::int_hex_const) {
        int res = 0, z = 1;
        while (i->state != &RG::pref_hex_const) {
            res += hex_digit(i->character)*z; z *= 16;
            ++i;
        }
        value = res;
    }
}

void Token_real_const::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_real_const
    FAStatesList::reverse_iterator i = ++list.rbegin();
    int whole = 0;
    double frac = 0.0;
    int deg = 0;
    if (i->state == &RG::real_const) {
        int z = 1;
        while (i->state == &RG::real_const) {
            deg += digit(i->character)*z; z *= 10;
            ++i;
        }
        if (i->state == &RG::real_const_e_sign) {
            if (i->character == '-')
                deg = -deg;
            ++i;
        }
        //i->state == real_const_e
        ++i;
    }
    //i->state == real_const_without_e
    while (i->character != '.') {
        frac = (frac + digit(i->character))/10;
        ++i;
    }
    ++i;
    int z = 1;
    while (i != list.rend()) {
        whole += digit(i->character)*z; z *= 10;
        ++i;
    }
    double res = whole + frac;
    if (deg > 0) {
        for (int i = 0; i < deg; ++i)
            res *= 10;
    }
    else if (deg < 0) {
        for (int i = 0; i < -deg; ++i)
            res /= 10;
    }
    value = res;
}

void Token_char_const::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_char_const
    FAStatesList::reverse_iterator i = ++list.rbegin();
    ++i;
    if (i->state == &RG::s_quote_char)
        value = i->character;
    else if (i->state == &RG::s_quote_back_slash_1_oct_digit ||
        i->state == &RG::s_quote_back_slash_2_oct_digits ||
        i->state == &RG::s_quote_back_slash_3_oct_digits) {
        int code = 0, z = 1;
        while (i->state != &RG::s_quote_back_slash) {
            code += digit(i->character)*z; z *= 8;
            ++i;
        }
        value = (char)code;
    }
    else if (i->state == &RG::s_quote_back_slash_x_hex_digits) {
        int code = 0, z = 1;
        while (i->state != &RG::s_quote_back_slash_x) {
            code += hex_digit(i->character)*z; z *= 16;
            ++i;
        }
        value = (char)code;
    }
    else if (i->state == &RG::s_quote_back_slash_char)
        value = escape_char(i->character);
}

void Token_string_const::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_string_const
    FAStatesList::reverse_iterator i = ++list.rbegin();
    ++i;
    value = "";
    while (i != list.rend()) {
        if (i->state == &RG::double_quote_chars) {
            char ch = i->character;
            ++i;
            if (i != list.rend()) {
                if (i->state == &RG::string_const)
                    ++i;
                else
                    value = ch + value;
            }
        }
        else if (i->state == &RG::d_quote_chars_back_slash_1_oct_digit ||
        i->state == &RG::d_quote_chars_back_slash_2_oct_digits ||
        i->state == &RG::d_quote_chars_back_slash_3_oct_digits) {
            int code = 0, z = 1;
            bool flag = false;
            while (!flag) {
                flag = (i->state == &RG::d_quote_chars_back_slash);
                code += digit(i->character)*z; z *= 8;
                ++i;
            }
            value = (char)code + value;
        }
        else if (i->state == &RG::d_quote_chars_back_slash_x_hex_digits) {
            int code = 0, z = 1;
            while (i->state != &RG::d_quote_chars_back_slash) {
                code += hex_digit(i->character)*z; z *= 16;
                ++i;
            }
            ++i;
            value = (char)code + value;
        }
        else if (i->state == &RG::d_quote_chars_back_slash_char) {
            value = escape_char(i->character) + value;
            ++i; ++i;
        }
    }
}

void Token_ident_or_keyword::CalcValue(FAStatesList& list)
{
    const int KEYWORDS_NUMBER = 32;
    const char* KEYWORDS_STR[KEYWORDS_NUMBER] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
        "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while"};
    value = IDENT_OR_KEYWORD_IDENT;
    for (int i = 0; i < KEYWORDS_NUMBER; ++i) {
        if (text == KEYWORDS_STR[i]) {
            value = (IdentifierOrKeywordT)(i+1);
            break;
        }
    }
}

void Token_operator::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_operator
    FAStatesList::reverse_iterator i = ++list.rbegin();
    value = static_cast<Nonterminal_usual_operator*>(i->state)->Op();
}

void Token_delimiter::CalcValue(FAStatesList& list)
{
    //последнее состояние в списке == token_delimiter
    FAStatesList::reverse_iterator i = ++list.rbegin();
    value = static_cast<Nonterminal_usual_delimiter*>(i->state)->Delim();
}

#pragma once

#include "utility/std.hpp"


namespace kh {
    enum class TokenType {
        IDENTIFIER, OPERATOR, SYMBOL,
        CHARACTER, STRING, BUFFER, 
        INTEGER, FLOATING, IMAGINARY
    };

    enum class Operator {
        ADD, SUB, MUL, DIV, MOD, POW,
        IADD, ISUB, IMUL, IDIV, IMOD, IPOW,
        INCREMENT, DECREMENT,

        EQUAL, NOT_EQUAL, LESS, MORE, LESS_EQUAL, MORE_EQUAL,

        BIT_AND, BIT_OR, BIT_NOT,
        BIT_LSHIFT, BIT_RSHIFT,
        AND, OR, NOT,

        ASSIGN, SIZEOF, SCOPE,
        TERNARY_IF, TERNARY_ELSE,

        STACK_INST
    };

    enum class Symbol {
        SEMICOLON, COMMA,

        PARENTHESES_OPEN, PARENTHESES_CLOSE,
        CURLY_OPEN, CURLY_CLOSE,
        SQUARE_OPEN, SQUARE_CLOSE,
        
        TEMPLATE_OPEN, TEMPLATE_CLOSE
    };
}

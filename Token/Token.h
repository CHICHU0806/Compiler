//
// Created by 20852 on 2026/5/10.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <string>

//Token类型
enum class TokenType {
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    LParen,
    RParen,
    End,
    Invalid
};

// Token基本的构成方式
struct Token {
    TokenType type;
    std::string text;
};

#endif //COMPILER_TOKEN_H

//
// Created by 20852 on 2026/5/10.
//

#include "../Inc/Lexer.h"

Lexer::Lexer(const std::string &input)  : input_(input), pos_(0) {}

Token Lexer::nextToken() {

    skipWhitespace();

    if (pos_ >= input_.size()) {
        return {TokenType::End, ""};
    }

    char ch = input_[pos_];

    if (std::isdigit(static_cast<unsigned char>(ch))) {
        return readNumber();
    }

    pos_++;

    switch (ch) {
        case '+':
            return {TokenType::Plus, "+"};
        case '-':
            return {TokenType::Minus, "-"};
        case '*':
            return {TokenType::Mul, "*"};
        case '/':
            return {TokenType::Div, "/"};
        case '(':
            return {TokenType::LParen, "("};
        case ')':
            return {TokenType::RParen, ")"};
        default:
            return {TokenType::Invalid, std::string(1, ch)};
    }
}

void Lexer::skipWhitespace() {
    //遍历过程中完成
    while (pos_ < input_.size() && std::isspace(static_cast<unsigned char>(input_[pos_]))){
        pos_++;
    }
}

Token Lexer::readNumber() {
    size_t start = pos_;

    while (pos_ < input_.size() && std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
        pos_++;
    }

    return {TokenType::Number,input_.substr(start,pos_-start)};
}
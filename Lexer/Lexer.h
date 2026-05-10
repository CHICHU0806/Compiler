//
// Created by 20852 on 2026/5/10.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
#include "token.h"

//词法分析器的构成，从左到右扫描并识别字符串
class Lexer {
public:
    explicit Lexer(const std::string& input) : input_(input), pos_(0) {
    }

    //关键函数，调用一次返回一个新Token
    Token nextToken() {

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


private:
    std::string input_;
    size_t pos_;

    //私有函数：跳过空格
    void skipWhitespace() {
        //遍历过程中完成
        while (pos_ < input_.size() && std::isspace(static_cast<unsigned char>(input_[pos_]))){
            pos_++;
        }
    }

    /*
     *读数字
     *但是其目的是为了在遍历过程中实现
    */
    Token readNumber() {
        size_t start = pos_;

        while (pos_ < input_.size() && std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
            pos_++;
        }

        return {TokenType::Number,input_.substr(start,pos_-start)};
    }
};

#endif //COMPILER_LEXER_H

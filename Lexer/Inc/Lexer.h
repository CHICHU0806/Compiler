//
// Created by 20852 on 2026/5/10.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
#include "Token.h"

//词法分析器的构成，从左到右扫描并识别字符串
class Lexer {
public:
    explicit Lexer(const std::string& input);

    //关键函数，调用一次返回一个新Token
    Token nextToken();


private:
    std::string input_;
    size_t pos_;

    //私有函数：跳过空格
    void skipWhitespace();

    /*
     *读数字
     *但是其目的是为了在遍历过程中实现
    */
    Token readNumber();
};

#endif //COMPILER_LEXER_H

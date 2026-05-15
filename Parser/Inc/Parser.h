//
// Created by 20852 on 2026/5/10.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <string>
#include "../../Lexer/Inc/Lexer.h"
#include <stdexcept>

// Parser语法分析器
class Parser {
public:
    explicit Parser(Lexer& lexer);

    int parse();

private:
    Lexer& lexer_;
    Token currentToken_;

    void advance();

    /*
     * 根据四则运算文法，括号优先级大于乘除大于加减，因此需要拆分三层去看
     * 也就是Expression>Term>Factor，然后再递归判断即可
     */
    int parseExpression();

    int parseTerm();

    int parseFactor();
};


#endif //COMPILER_PARSER_H

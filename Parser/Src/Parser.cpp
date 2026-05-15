//
// Created by 20852 on 2026/5/10.
//

#include "../Inc/Parser.h"

Parser::Parser(Lexer &lexer) : lexer_(lexer) ,currentToken_(lexer_.nextToken()) {
}

int Parser::parse() {
    int result = parseExpression();

    if (currentToken_.type != TokenType::End) {
        throw std::runtime_error("Unexpected token: " + currentToken_.text); //如果解析完了还有剩余的Token就报错
    }

    return result;
}

void Parser::advance() {
    currentToken_ = lexer_.nextToken();
}

int Parser::parseExpression() {
    int left = parseTerm(); //首先对左侧做乘除的解析

    while (currentToken_.type == TokenType::Plus || currentToken_.type == TokenType::Minus) {
        TokenType op = currentToken_.type;
        advance();

        int right = parseTerm(); //再对右侧做乘除的解析

        if (op == TokenType::Plus) {
            left += right; //如果是加法就把左侧和右侧的值相加
        } else {
            left -= right; //如果是减法就把左侧和右侧的值相减
        }
    }

    return left;
}

int Parser::parseTerm() {
    int left = parseFactor(); //首先对左侧做括号的解析

    while (currentToken_.type == TokenType::Mul || currentToken_.type == TokenType::Div) {
        TokenType op = currentToken_.type;
        advance();

        int right = parseFactor(); //再对右侧做括号的解析

        if (op == TokenType::Mul) {
            left *= right; //如果是乘法就把左侧和右侧的值相乘
        } else {
            if (right == 0) {
                throw std::runtime_error("Division by zero"); //如果是除法就要注意除数不能为零
            }
            left /= right; //如果是除法就把左侧的值除以右侧的值
        }
    }

    return left;
}

int Parser::parseFactor() {
    if (currentToken_.type == TokenType::Number) {
        int value = std::stoi(currentToken_.text); //如果是数字就把它从字符串转化为整数
        advance();
        return value;
    }

    if (currentToken_.type == TokenType::LParen) {
        advance();

        int value = parseExpression(); //递归调用解析括号内的表达式

        if (currentToken_.type != TokenType::RParen) {
            throw std::runtime_error("Expected ')'"); //如果只有左括号没有右括号就报错
        }

        advance();
        return value;
    }

    throw std::runtime_error("Expected number or '('");
}

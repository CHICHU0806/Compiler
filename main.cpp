#include <iostream>
#include "Token.h"
#include "Lexer/Inc/Lexer.h"
#include "Parser/Inc/Parser.h"

/*
 * 因为枚举的类型不能直接输出，因此需要将TokenType转换为字符串，便于输出
*/
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Number:
            return "Number";
        case TokenType::Plus:
            return "Plus";
        case TokenType::Minus:
            return "Minus";
        case TokenType::Mul:
            return "Mul";
        case TokenType::Div:
            return "Div";
        case TokenType::LParen:
            return "LParen";
        case TokenType::RParen:
            return "RParen";
        case TokenType::End:
            return "End";
        case TokenType::Invalid:
            return "Invalid";
        default:
            return "Unknown";
    }
}

int main() {
    std::string input;

    std::cout << "Input expression: ";
    std::getline(std::cin, input);

    try {
        Lexer lexer(input);
        Parser parser(lexer);

        int result = parser.parse();

        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }


    return 0;
}
#include <iostream>
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

//词法分析器的构成
class Lexer {
public:
    explicit Lexer(const std::string& input) : input_(input), pos_(0) {
    }

    Token nextToken() {

    }


private:
    std::string input_;
    size_t pos_;

    //私有函数：跳过空格
    void skipWhitespace() {
        while (pos_ < input_.size() && std ::isspace(input_[pos_])) {}
    }
};
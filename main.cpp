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

// Parser语法分析器
class Parser {
public:
    explicit Parser(Lexer& lexer) : lexer_(lexer) ,currentToken_(lexer_.nextToken()) {
    }

    int parse() {
        int result = parseExpression();

        if (currentToken_.type != TokenType::End) {
            throw std::runtime_error("Unexpected token: " + currentToken_.text); //如果解析完了还有剩余的Token就报错
        }

        return result;
    }

private:
    Lexer& lexer_;
    Token currentToken_;

    void advance() {
        currentToken_ = lexer_.nextToken();
    }

    /*
     * 根据四则运算文法，括号优先级大于乘除大于加减，因此需要拆分三层去看
     * 也就是Expression>Term>Factor，然后再递归判断即可
     */
    int parseExpression() {
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

    int parseTerm() {
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

    int parseFactor() {
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
};


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
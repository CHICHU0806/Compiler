cmake_minimum_required(VERSION 4.2)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp
        Token/token.h
        Lexer/Src/Lexer.cpp
        Lexer/Inc/Lexer.h
        Parser/Src/Parser.cpp
        Parser/Inc/Parser.h
        AST/Expr.h)

include_directories(
        ./AST
        ./Token
        ./Lexer/Inc
        ./Lexer/Src
        ./Parser/Inc
        ./Parser/Src
)
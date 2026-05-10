cmake_minimum_required(VERSION 4.2)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp
        Token/token.h
        Lexer/Lexer.cpp
        Lexer/Lexer.h
        Parser/Src/Parser.cpp
        Parser/Inc/Parser.h)

include_directories(
        ./Token
        ./Lexer
        ./Parser/Inc
        ./Parser/Src
)
import sys
from antlr4 import *


def hello_main():
    from gen_output.HelloLexer import HelloLexer
    from gen_output.HelloParser import HelloParser
    input_stream = FileStream("test_data/input.txt")
    lexer = HelloLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = HelloParser(stream)
    tree = parser.r()
    print(tree.toStringTree(recog=parser))


def cpp_main():
    from gen_output.CPP14Lexer import CPP14Lexer
    from gen_output.CPP14Parser import CPP14Parser

    input_stream = FileStream("test_data/main.cpp")
    lexer = CPP14Lexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = CPP14Parser(stream)
    tree = parser.literal()
    print(tree.toStringTree(recog=parser))


if __name__ == '__main__':
    hello_main()
    cpp_main()

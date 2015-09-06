#include "ola.h"
#include <iostream>

namespace ola {

OlaToLlvmCompiler::OlaToLlvmCompiler()
{
	
}

OlaToLlvmCompiler::~OlaToLlvmCompiler()
{

}

void OlaToLlvmCompiler::feed(std::string code)
{
    _lexer.loadBuffer(code.c_str());

    std::cout << "tokens: ";
    Token t;
    do {
        t = _lexer.nextToken();

        std::cout << (int)t << " ";

    } while (t != Token::Eob);
    std::cout << "\n";
}

}
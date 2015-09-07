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
        compileProgram();
       /* std::cout << "tokens: ";
        Token t;

        do {
            t = _lexer.nextToken();

            std::cout << (int)t << " ";

        } while (t != Token::Eob);
        std::cout << "\n";*/
    }



    void OlaToLlvmCompiler::compileProgram() {
        //get the first token
        _curTok = _lexer.nextToken();

        switch (_curTok) {
            case Token::Eob:
            case Token::Eof:
                std::cout << "successfully parsed program\n";
                return;
            default:
                compileBlock();
                break;
        }
    }

    void OlaToLlvmCompiler::compileNumeric() {
        
    }

    void OlaToLlvmCompiler::compileBlock() {
        if (_curTok == Token::Type) {

        } else if (_curTok == Token::Identifier) {

        }
    }
}
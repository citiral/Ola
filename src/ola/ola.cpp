#include "ola.h"
#include <llvm/ADT/STLExtras.h>
#include <stdlib.h>
#include <iostream>
#include "compileassert.h"


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
        /*std::cout << "tokens: ";
        while (!_lexer.atEndOfBuffer())
            std::cout << (int)_lexer.nextToken() << " ";
        std::cout << "\n";*/
        compileProgram();
    }

    void OlaToLlvmCompiler::compileProgram() {
        //get the first token
        _lexer.nextToken();

        //keep looping untill we are out of tokens
        while (!_lexer.atEndOfBuffer()) {
            //try to delegate the token to the correct compile function
            switch (_lexer.curToken()) {
                case Token::Eob:
                case Token::Eof:
                    std::cout << "successfully parsed program\n";
                    return;
                default:
                    compileBlock()->log(std::cout);
                    break;
            }
        }
    }

    std::unique_ptr<ASTNode> OlaToLlvmCompiler::compileBlock() {
        switch (_lexer.curToken()) {
            case Token::Function:
                return FunctionAST::generate(_lexer);
            default:
                COMPILE_GENERATE_AND_RETURN_ERROR(_lexer, "Unknown token in block.");
        }
    }
}
#include "ola.h"
#include <llvm/ADT/STLExtras.h>
#include <stdlib.h>
#include <iostream>
#include "astassert.h"

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

        //first, generate the AST
        std::vector<std::unique_ptr<ASTNode>> astRoot;

        //keep looping untill we are out of tokens
        while (!_lexer.atEndOfBuffer()) {
            //try to delegate the token to the correct compile function
            switch (_lexer.curToken()) {
                case Token::Eob:
                case Token::Eof:
                    std::cout << "successfully parsed program\n";
                    return;
                default:
                    auto elem = compileBlock();
                    elem->log(std::cout);
                    astRoot.push_back(std::move(elem));
                    break;
            }
        }

        Context c;
        TypePass typePass(c);

        //first, we do the type pass
        for (u32 i = 0 ; i < astRoot.size() ; i++) {
            astRoot[i]->visit(typePass);
        }
    }

    std::unique_ptr<ASTNode> OlaToLlvmCompiler::compileBlock() {

        switch (_lexer.curToken()) {
            case Token::Function: {
                auto f = FunctionAST::generate(_lexer);
                return std::move(f);
            } default:
                COMPILE_GENERATE_AND_RETURN_ERROR(_lexer, "Unknown token in block.");
        }
    }
}
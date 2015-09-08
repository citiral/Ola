#include "ola.h"
#include <llvm/ADT/STLExtras.h>
#include <stdlib.h>
#include <iostream>

#define COMPILE_GENERATE_AND_RETURN_ERROR(message) \
{\
    std::cout << "Error: " << message << "\n";\
    nextToken();\
    return nullptr;\
}

#define COMPILE_RETURN_ERROR(message) \
{\
    std::cout << "Error: " << message << "\n";\
    return nullptr;\
}
/*
#define COMPILE_ASSERT_TOKEN_TYPE_EQUALS(x, message) \
{\
 if (_curTok != x) {\
        COMPILE_RETURN_ERROR(message);\
    }\
}*/

#define TOKEN_TYPE_NOT_EQUALS(x) (_curTok != x)
#define TOKEN_TYPE_EQUALS(x) (_curTok == x)
#define OR(x, y) (x || y)

#define COMPILE_ASSERT(condition, message) \
{\
    if (!condition) {\
        COMPILE_RETURN_ERROR(message);\
    }\
}

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
        /*std::cout << "tokens: ";
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

        //keep looping untill we are out of tokens
        while (!_lexer.atEndOfBuffer()) {
            //try to delegate the token to the correct compile function
            switch (_curTok) {
                case Token::Numeric:
                    compileNumeric()->log(std::cout);
                    return;
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
        switch (_curTok) {
            case Token::Function:
                return compileFunction();
            default:
                COMPILE_GENERATE_AND_RETURN_ERROR("Unknown token in block.");
        }
    }

    std::unique_ptr<ASTNode> OlaToLlvmCompiler::compileGenerateError(std::string error) {
        nextToken(); //eat the current token
        std::cout << "Error: " << error << "\n";
        return nullptr;
    }

    std::unique_ptr<FunctionAST> OlaToLlvmCompiler::compileFunction() {
        auto prototype = compileFunctionPrototype();

        //we should be at the brackets now
        COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Char_openCurlyBracket), "Expected { after function declaration.");
        nextToken();

        auto body = compileExpressionSeries();

        //and it should be closed now
        COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Char_closeCurlyBracket), "Expected } At the end of the function body.");
        nextToken();


        return llvm::make_unique<FunctionAST>(std::move(prototype), std::move(body));
    }

    std::unique_ptr<FunctionPrototypeAST> OlaToLlvmCompiler::compileFunctionPrototype() {
        //eat the function token
        nextToken();
        //get the name of the function and eat it
        COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Identifier), "Expected identifier in function prototype.");
        std::string name = _lexer.value.string;
        nextToken();

        std::vector<std::string> args;
        std::vector<std::string> types;
        std::string type;

        //make sure we are now in brackets
        COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Char_openRoundBracket), "Expected '(' after function identifier.");

        //keep fetching pairs of tokens until we have no more commas
        do {
            nextToken();
            //eat the type
            COMPILE_ASSERT(OR(TOKEN_TYPE_EQUALS(Token::Identifier), TOKEN_TYPE_EQUALS(Token::Type)), "Parameter should start with a type.");
            types.push_back(_lexer.value.string);
            nextToken();
            //and the name
            COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Identifier), "Parameter should end with an identifier.");
            args.push_back(_lexer.value.string);
            nextToken();
        } while (_curTok == Token::Char_comma);

        //brackets should be closed
        COMPILE_ASSERT(TOKEN_TYPE_EQUALS(Token::Char_closeRoundBracket), "Expected ')' after function argument list.");
        nextToken();
        //if the next token is a ->, we get the type
        if (_curTok == Token::Char_arrow) {
            nextToken();
            COMPILE_ASSERT(OR(TOKEN_TYPE_EQUALS(Token::Identifier), TOKEN_TYPE_EQUALS(Token::Type)), "Function return type is not a type.");
            type = _lexer.value.string;
            nextToken();
        } else {
            type = "void";
        }
        return llvm::make_unique<FunctionPrototypeAST>(type, name, std::move(args), std::move(types));
    }

    std::unique_ptr<ExpressionSeriesAST> OlaToLlvmCompiler::compileExpressionSeries() {
        std::vector<std::unique_ptr<ExpressionAST>> expressions;

        //a statement series ends with a curly bracket
        while (!TOKEN_TYPE_EQUALS(Token::Char_closeCurlyBracket)) {
            expressions.push_back(std::move(compileExpression()));
        }

        return llvm::make_unique<ExpressionSeriesAST>(std::move(expressions));
    }

    std::unique_ptr<ExpressionAST> OlaToLlvmCompiler::compileExpression() {
        switch (_curTok) {
            case Token::Numeric:
                return compileNumeric();
            default:
                COMPILE_GENERATE_AND_RETURN_ERROR("Unknown token in expression");
        }
    }

    std::unique_ptr<NumberIntegerAST> OlaToLlvmCompiler::compileNumeric() {
        i64 number = atol(_lexer.value.string.c_str());
        nextToken();
        return llvm::make_unique<NumberIntegerAST>(number);
    }


    Token OlaToLlvmCompiler::nextToken() {
        return _curTok = _lexer.nextToken();
    }
}
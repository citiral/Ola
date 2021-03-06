//
// Created by citiral on 9/8/15.
//

#include "FunctionPrototypeAST.h"
#include <llvm/ADT/STLExtras.h>
#include "../types.h"
#include "../astassert.h"
#include "../codegenassert.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

namespace ola {
    FunctionPrototypeAST::FunctionPrototypeAST(Lexer& l, std::string type, std::string name, std::vector<std::string> args,
                                               std::vector<std::string> types):
            ASTNode(l),
            _typeName(type),
            _name(name),
            _args(std::move(args)),
            _argsTypesNames(types) { }

    std::unique_ptr<FunctionPrototypeAST> FunctionPrototypeAST::generate(Lexer &l) {
        //eat the function token
        l.nextToken();
        //get the name of the function and eat it
        COMPILE_ASSERT(l.curToken() == Token::Identifier, "Expected identifier in function prototype.");
        std::string name = l.value.string;
        l.nextToken();

        std::vector<std::string> args;
        std::vector<std::string> types;
        std::string type;

        //make sure we are now in brackets
        COMPILE_ASSERT(l.curToken() == Token::Char_openRoundBracket, "Expected '(' after function identifier.");
        l.nextToken();

        //keep fetching pairs of tokens until we have no more commas
        while (l.curToken() != Token::Char_closeRoundBracket) {
            //eat the type
            COMPILE_ASSERT(l.curToken() == Token::Identifier || l.curToken() == Token::Type, "Parameter should start with a type.");
            types.push_back(l.value.string);
            l.nextToken();
            //and the name
            COMPILE_ASSERT(l.curToken() == Token::Identifier, "Parameter should end with an identifier.");
            args.push_back(l.value.string);
            l.nextToken();

            //if we do not have a ',' break
            if (l.curToken() != Token::Char_comma)
                break;
            l.nextToken();
        }

        //brackets should be closed
        COMPILE_ASSERT(l.curToken() == Token::Char_closeRoundBracket, "Expected ')' after function argument list.");
        l.nextToken();
        //if the next token is a ->, we get the type
        if (l.curToken() == Token::Char_arrow) {
            l.nextToken();
            COMPILE_ASSERT(l.curToken() == Token::Identifier || l.curToken() == Token::Type, "Function return type is not a type.");
            type = l.value.string;
            l.nextToken();
        } else {
            type = "void";
        }
        return llvm::make_unique<FunctionPrototypeAST>(l, type, name, std::move(args), std::move(types));
    }

    Type* FunctionPrototypeAST::getType() {
        return _type;
    }

    void FunctionPrototypeAST::setType(Type* type) {
        _type = type;
    }

    std::string FunctionPrototypeAST::getTypeName() {
        return _typeName;
    }

    std::string FunctionPrototypeAST::getFunctionName() {
        return _name;
    }

    const std::vector<Type*>& FunctionPrototypeAST::getArgsTypes() {
        return _argsTypes;
    }

    void FunctionPrototypeAST::setArgsTypes(std::vector<Type*> argsTypes) {
        _argsTypes = std::move(argsTypes);
    }

    const std::vector<std::string>& FunctionPrototypeAST::getArgsNames() {
        return _args;
    }

    const std::vector<std::string>& FunctionPrototypeAST::getArgsTypesNames() {
        return _argsTypesNames;
    }
}
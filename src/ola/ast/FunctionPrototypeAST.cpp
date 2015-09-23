//
// Created by citiral on 9/8/15.
//

#include "FunctionPrototypeAST.h"
#include "../types.h"
#include "../astassert.h"
#include "../codegenassert.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

namespace ola {
    FunctionPrototypeAST::FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args,
                                               std::vector<std::string> types)
            : _type(type),
              _name(name),
              _args(std::move(args)),
              _types(types) { }

    void FunctionPrototypeAST::log(std::ostream &s) {
        s << "Function prototype: " << _name << "(";
        if (_args.size() > 0)
            s << _types[0] << " " << _args[0];
        for (u32 i = 1; i < _args.size(); i++) {
            s << ", " << _types[i] << " " << _args[i];
        }
        s << ") -> " << _type << "\n";
    }

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
        return llvm::make_unique<FunctionPrototypeAST>(type, name, std::move(args), std::move(types));
    }

    llvm::Function* FunctionPrototypeAST::codegen(Context* c) {
        std::vector<llvm::Type*> types;

        //first, parse all the types
        for (u32 i = 0 ; i < _types.size() ; i++) {
            llvm::Type* t = c->getType(_types[i]);
            CODEGEN_ASSERT(t != nullptr, "Unknown type " << _types[i]);
	        types.push_back(t);
        }

	    llvm::FunctionType* funcType = llvm::FunctionType::get(c->getType(_type), types, false);
	    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, _name, c->module.get());

	    u32 i = 0;
	    for (auto& arg : func->args()) {
			arg.setName(_args[i++]);
	    }

	    //insert the function into the context
	    c->getScope()->addFunction(_name, func);

	    return func;
    }

    std::unique_ptr<FunctionPrototypeDAST> FunctionPrototypeAST::generateDecoratedTree(DastContext& context) {
        return llvm::make_unique<FunctionPrototypeDAST>(context, _name, _type, _args);
    }
}
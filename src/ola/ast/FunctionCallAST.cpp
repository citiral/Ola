//
// Created by citiral on 9/9/15.
//

#include "FunctionCallAST.h"
#include "../compileassert.h"
#include "../types.h"
#include "../codegenassert.h"

using namespace llvm;

ola::FunctionCallAST::FunctionCallAST(std::string func, std::vector<std::unique_ptr<ola::ExpressionAST>> args)
    : _func(func),
      _args(std::move(args)) {}


std::unique_ptr<ola::FunctionCallAST> ola::FunctionCallAST::generate(std::string functionname, ola::Lexer &l) {
    //the first token should be a '('
    COMPILE_ASSERT(l.curToken() == Token::Char_openRoundBracket, "Expected a '(' in function call. Compiler error?");
    l.nextToken();

    std::vector<std::unique_ptr<ExpressionAST>> args;

    while (l.curToken() != Token::Char_closeRoundBracket) {
        auto expr = ExpressionAST::generate(l);
        if (expr == nullptr)
            return nullptr;
        args.push_back(std::move(expr));

        //if the next token is not a ',', break out of the loop
        if (l.curToken() != Token::Char_comma)
            break;
        l.nextToken();
    }
    COMPILE_ASSERT(l.curToken() == Token::Char_closeRoundBracket, "Expected ')' at the end of a function call");

    //eat the close bracket
    l.nextToken();

    return std::make_unique<FunctionCallAST>(functionname, std::move(args));
}

void ola::FunctionCallAST::log(std::ostream &s) {
    s << _func << "(";
    if (_args.size() > 1)
        _args[0]->log(s);
    for (u32 i = 1 ; i < _args.size() ; i++) {
        s << ", ";
        _args[i]->log(s);
    }
    s << ")";
}

Value* ola::FunctionCallAST::codegen(ola::Context* c) {
    llvm::Function* func = c->getScope()->getFunction(_func);
    CODEGEN_ASSERT(func != nullptr, "Undefined function " << _func);
    std::vector<llvm::Value*> args;
    for (u32 i = 0 ; i < _args.size() ; i++) {
        args.push_back(_args[i]->codegen(c));
        //the argument needs to be valid
        if (args.back() == nullptr)
            return nullptr;
        //check if the type is valid
        CODEGEN_ASSERT(func->getFunctionType()->params()[i] == args.back()->getType(), "Invalid type in function call. Expected " << func->getFunctionType()->params()[i] << " got " << args.back()->getType());

    }

    return c->builder.CreateCall(func, args, _func.c_str());
}

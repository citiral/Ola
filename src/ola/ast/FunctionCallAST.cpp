//
// Created by citiral on 9/9/15.
//

#include "FunctionCallAST.h"
#include <llvm/ADT/STLExtras.h>
#include "../astassert.h"
#include "../types.h"
#include "../codegenassert.h"

using namespace llvm;

ola::FunctionCallAST::FunctionCallAST(Lexer& l, std::string func, std::vector<std::unique_ptr<ola::ExpressionAST>> args):
        ExpressionAST(l),
        _func(func),
        _args(std::move(args)),
        _type(nullptr) {}


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

    return llvm::make_unique<FunctionCallAST>(l, functionname, std::move(args));
}

ola::Type* ola::FunctionCallAST::getType() {
    return _type;
}

void ola::FunctionCallAST::setType(ola::Type* type) {
    _type = type;
}

std::string ola::FunctionCallAST::getFunctionName() {
    return _func;
}

std::vector<std::unique_ptr<ola::ExpressionAST>>* ola::FunctionCallAST::getArgs() {
    return &_args;
}

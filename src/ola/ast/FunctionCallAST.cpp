//
// Created by citiral on 9/9/15.
//

#include "FunctionCallAST.h"
#include "../astassert.h"
#include "../types.h"
#include "../codegenassert.h"
#include "../dast/FunctionCallDAST.h"

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

    return llvm::make_unique<FunctionCallAST>(functionname, std::move(args));
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

ola::Type* ola::FunctionCallAST::getType() {
    return _type;
}

void ola::FunctionCallAST::setType(ola::Type* type) {
    _type = type;
}

std::string ola::FunctionCallAST::getFunctionName() {
    return _func;
}

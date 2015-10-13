//
// Created by citiral on 9/8/15.
//

#include "FunctionAST.h"
#include "../astassert.h"
#include <llvm/IR/Function.h>
#include <llvm/ADT/STLExtras.h>

namespace ola {
    FunctionAST::FunctionAST(Lexer& l, std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body):
            ASTNode(l),
            _prototype(std::move(prototype)),
            _body(std::move(body)) { }

    std::unique_ptr<FunctionAST> FunctionAST::generate(Lexer &l) {
        auto prototype = FunctionPrototypeAST::generate(l);

        //we should be at the brackets now
        COMPILE_ASSERT(l.curToken() == Token::Char_openCurlyBracket, "Expected { after function declaration.");
        l.nextToken();

        auto body = ExpressionSeriesAST::generate(l);

        //and it should be closed now
        COMPILE_ASSERT(l.curToken() == Token::Char_closeCurlyBracket, "Expected } At the end of the function body.");
        l.nextToken();

        return llvm::make_unique<FunctionAST>(l, std::move(prototype), std::move(body));
    }

    FunctionPrototypeAST* FunctionAST::getPrototype() {
        return _prototype.get();
    }

    ExpressionSeriesAST* FunctionAST::getExpressionSeries() {
        return _body.get();
    }
}
//
// Created by citiral on 9/8/15.
//

#include "FunctionAST.h"
#include "../compileassert.h"

namespace ola {
    FunctionAST::FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body)
            : _prototype(std::move(prototype)),
              _body(std::move(body)) { }

    void FunctionAST::log(std::ostream &s) {
        _prototype->log(s);
        _body->log(s);
    }

    std::unique_ptr<FunctionAST> FunctionAST::generate(Lexer &l) {
        auto prototype = FunctionPrototypeAST::generate(l);

        //we should be at the brackets now
        COMPILE_ASSERT(l.curToken() == Token::Char_openCurlyBracket, "Expected { after function declaration.");
        l.nextToken();

        auto body = ExpressionSeriesAST::generate(l);

        //and it should be closed now
        COMPILE_ASSERT(l.curToken() == Token::Char_closeCurlyBracket, "Expected } At the end of the function body.");
        l.nextToken();

        COMPILE_ASSERT(body->type() == prototype->type(), "Return value is of incorrect type");

        return std::make_unique<FunctionAST>(std::move(prototype), std::move(body));
    }
}
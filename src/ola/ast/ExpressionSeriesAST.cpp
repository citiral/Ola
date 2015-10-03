//
// Created by citiral on 9/8/15.
//

#include <llvm/ADT/STLExtras.h>
#include "ExpressionSeriesAST.h"
#include "ExpressionKillerAST.h"
#include "../astassert.h"

namespace ola {
    ExpressionSeriesAST::ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body)
            : _body(std::move(body)),
              _type(nullptr) { }

    std::unique_ptr<ExpressionSeriesAST> ExpressionSeriesAST::generate(Lexer &l) {
        std::vector<std::unique_ptr<ExpressionAST>> expressions;

        //a statement series ends with a curly bracket
        while (1) {
            //if there is a close curly bracket, stop the series
            if (l.curToken() == Token::Char_closeCurlyBracket) {
                return llvm::make_unique<ExpressionSeriesAST>(std::move(expressions));
            }

            //parse an expression
            auto expr = ExpressionAST::generate(l);

            if (expr != nullptr) {
                if (l.curToken() == Token::Char_semicolon) {
                    //generate an expressionkiller
                    expressions.push_back(llvm::make_unique<ExpressionKillerAST>(std::move(expr)));
                    //eat the semicolon and continue
                    l.nextToken();
                } else if (l.curToken() == Token::Char_closeCurlyBracket) {
                    expressions.push_back(std::move(expr));
                } else {
                    COMPILE_GENERATE_AND_RETURN_ERROR(l, "Expected ';' or '}' in expressionseries.");
                }
            }
        }
    }

    Type* ExpressionSeriesAST::getType() {
        return (*_body.end())->getType();
    }

    void ExpressionSeriesAST::setType(Type* type) {
        _type = type;
    }

    std::vector<std::unique_ptr<ExpressionAST>>* ExpressionSeriesAST::getBody() {
        return &_body;
    }
}
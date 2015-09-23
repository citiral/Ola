//
// Created by citiral on 9/8/15.
//

#include "ExpressionSeriesAST.h"
#include "ExpressionKillerAST.h"
#include "../astassert.h"

namespace ola {
    ExpressionSeriesAST::ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body)
            : _body(std::move(body)) { }

    void ExpressionSeriesAST::log(std::ostream &s) {
        s << "expression series: ";
        for (u32 i = 0; i < _body.size(); i++) {
            _body[i]->log(s);
            s << "\n";
        }
    }

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

    llvm::Value* ExpressionSeriesAST::codegen(Context* c) {
        llvm::Value* last = nullptr;
        for (u32 i = 0 ; i < _body.size() ; i++)
            last = _body[i]->codegen(c);
        return last;
    }

    std::unique_ptr<ExpressionDAST> ExpressionSeriesAST::generateDecoratedTree(DastContext& context) {
        return generateDecoratedTreeExpressionSeries(context);
    }

    std::unique_ptr<ExpressionSeriesDAST> ExpressionSeriesAST::generateDecoratedTreeExpressionSeries(
            DastContext& context) {
        std::vector<std::unique_ptr<ExpressionDAST>> expressions;

        for (u32 i = 0 ; i < _body.size() ; i++)
            expressions.push_back(std::move(_body[i]->generateDecoratedTree(context)));

        return llvm::make_unique<ExpressionSeriesDAST>(context, std::move(expressions));
    }
}
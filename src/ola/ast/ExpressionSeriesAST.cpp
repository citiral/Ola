//
// Created by citiral on 9/8/15.
//

#include "ExpressionSeriesAST.h"

namespace ola {
    ExpressionSeriesAST::ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body)
            : _body(std::move(body)) { }

    std::string ExpressionSeriesAST::type() {
        return _body.back()->type();
    }

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
        while (!(l.curToken() == Token::Char_closeCurlyBracket)) {
            expressions.push_back(std::move(ExpressionAST::generate(l)));
        }

        return std::make_unique<ExpressionSeriesAST>(std::move(expressions));
    }
}
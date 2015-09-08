//
// Created by citiral on 9/9/15.
//

#include "ExpressionKillerAST.h"

namespace ola {

    ExpressionKillerAST::ExpressionKillerAST(std::unique_ptr<ExpressionAST> expression)
        : _expression(std::move(expression)) {}

    std::string ExpressionKillerAST::type() {
        return "void";
    }

    void ExpressionKillerAST::log(std::ostream &s) {
        _expression->log(s);
        s << ";";
    }
}
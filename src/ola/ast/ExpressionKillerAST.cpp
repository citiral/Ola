//
// Created by citiral on 9/9/15.
//

#include "ExpressionKillerAST.h"

using namespace llvm;

namespace ola {

    ExpressionKillerAST::ExpressionKillerAST(std::unique_ptr<ExpressionAST> expression)
        : _expression(std::move(expression)),
          _type(nullptr) {}

    Type* ExpressionKillerAST::getType() {
        return _type;
    }

    void ExpressionKillerAST::setType(Type* type) {
        _type = type;
    }

    ExpressionAST* ExpressionKillerAST::getExpression() {
        return _expression.get();
    }
}
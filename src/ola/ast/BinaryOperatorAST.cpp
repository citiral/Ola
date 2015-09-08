//
// Created by citiral on 9/8/15.
//

#include "BinaryOperatorAST.h"

namespace ola {
    BinaryOperatorAST::BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression,
                                         std::unique_ptr<ExpressionAST> rightExpression)
            : _operator(opp),
              _leftExpression(std::move(leftExpression)),
              _rightExpression(std::move(rightExpression)) { }
}
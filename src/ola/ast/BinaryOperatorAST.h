//
// Created by citiral on 9/8/15.
//

#ifndef OLA_BINARYOPERATORAST_H
#define OLA_BINARYOPERATORAST_H

#include "ExpressionAST.h"
#include <memory>

namespace ola {
    class BinaryOperatorAST : public ExpressionAST {
    public:
        BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression,
                          std::unique_ptr<ExpressionAST> rightExpression);

    private:
        char _operator;
        std::unique_ptr<ExpressionAST> _leftExpression;
        std::unique_ptr<ExpressionAST> _rightExpression;
    };
}

#endif //OLA_BINARYOPERATORAST_H

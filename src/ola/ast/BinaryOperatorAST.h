//
// Created by citiral on 9/8/15.
//

#ifndef OLA_BINARYOPERATORAST_H
#define OLA_BINARYOPERATORAST_H

#include "ExpressionAST.h"
#include "../types.h"
#include <memory>

#define PRECEDENCE_UNKNOWN 1
#define PRECEDENCE_PLUS 20
#define PRECEDENCE_MIN  20
#define PRECEDENCE_MUL  40
#define PRECEDENCE_DIV  40

namespace ola {
    class BinaryOperatorAST : public ExpressionAST {
    public:
        BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression,
                          std::unique_ptr<ExpressionAST> rightExpression);

        void log(std::ostream &s) override;

        static u32 getPrecendence(char opp);

        std::unique_ptr<DASTNode> generateDecoratedTree(DastContext& context) override;
        std::unique_ptr<ExpressionDAST> generateDecoratedTreeExpression(DastContext& context) override;

        //fully parses calculation starting from the current state of the lexer. The LHS must already have been parsed
        static std::unique_ptr<ExpressionAST> generate(Lexer& l, std::unique_ptr<ExpressionAST> LHS);

    private:
        char _operator;
        std::unique_ptr<ExpressionAST> _leftExpression;
        std::unique_ptr<ExpressionAST> _rightExpression;
    };
}

#endif //OLA_BINARYOPERATORAST_H

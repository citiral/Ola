//
// Created by citiral on 9/8/15.
//

#include "BinaryOperatorAST.h"
#include "../astassert.h"
#include "../codegenassert.h"
#include "../dast/BinaryOperatorDAST.h"

namespace ola {
    BinaryOperatorAST::BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression,
                                         std::unique_ptr<ExpressionAST> rightExpression)
            : _operator(opp),
              _leftExpression(std::move(leftExpression)),
              _rightExpression(std::move(rightExpression)) { }

    u32 BinaryOperatorAST::getPrecendence(char opp) {
        if (opp == '+')
            return PRECEDENCE_PLUS;
        else if (opp == '-')
            return PRECEDENCE_MIN;
        else if (opp == '/')
            return PRECEDENCE_DIV;
        else if (opp == '*')
            return PRECEDENCE_MUL;
        return PRECEDENCE_UNKNOWN;
    }

    std::unique_ptr<ExpressionAST> BinaryOperatorAST::generate(Lexer &l, std::unique_ptr<ExpressionAST> LHS) {
        //this is the topmost expression
        auto expr = std::move(LHS);

        while (l.curToken() == Token::Operator) {
            //we eat the current operator
            char opp = l.value.character;
            l.nextToken();

            //then we parse the RHS
            auto RHS = ExpressionAST::generatePrimary(l);
            if (RHS == nullptr)
                return nullptr;

            //if the next token is an operator
            if (l.curToken() == Token::Operator) {
                //we look ahead, if the new operator has higher precedence than this one, parse it recursively
                if (getPrecendence(opp) < getPrecendence(l.value.character)) {
                    RHS = std::move(generate(l, std::move(RHS)));
                }
            }

            //merge the expressions
            expr = llvm::make_unique<BinaryOperatorAST>(opp, std::move(expr), std::move(RHS));
        }

        return std::move(expr);
    }

    void BinaryOperatorAST::log(std::ostream &s) {
        s << "(";
        _leftExpression->log(s);
        s << ")";
        s << " " << _operator << " ";
        s << "(";
        _rightExpression->log(s);
        s << ")";
    }

    std::unique_ptr<DASTNode> BinaryOperatorAST::generateDecoratedTree(DastContext& context) {
        return generateDecoratedTreeExpression(context);
    }

    std::unique_ptr<ExpressionDAST> BinaryOperatorAST::generateDecoratedTreeExpression(DastContext& context) {
        return llvm::make_unique<BinaryOperatorDAST>(context,
                                                     _leftExpression->generateDecoratedTreeExpression(context),
                                                     _rightExpression->generateDecoratedTreeExpression(context),
                                                     _operator);
    }
}
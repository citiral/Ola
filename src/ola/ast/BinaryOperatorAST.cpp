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

    llvm::Value* BinaryOperatorAST::codegen(Context* c) {
        //first codegen both arms
        auto LHS = _leftExpression->codegen(c);
        auto RHS = _rightExpression->codegen(c);

        if (!LHS || !RHS)
            return nullptr;

        CODEGEN_ASSERT(LHS->getType() == RHS->getType(), "Types in binary operation should be equal.");

        if (_operator == '+')
            return c->builder.CreateAdd(LHS, RHS, "binadd");
        if (_operator == '-')
            return c->builder.CreateSub(LHS, RHS, "binsub");
        if (_operator == '*')
            return c->builder.CreateMul(LHS, RHS, "binmul");
        if (_operator == '/')
            return c->builder.CreateSDiv(LHS, RHS, "bindiv");

        CODEGEN_RETURN_ERROR("Unknown operator '" << _operator << "'");
    }

    std::unique_ptr<ExpressionDAST> BinaryOperatorAST::generateDecoratedTree(DastContext& context) {
        return llvm::make_unique<BinaryOperatorDAST>(context,
                                                     _leftExpression->generateDecoratedTree(context),
                                                     _rightExpression->generateDecoratedTree(context),
                                                     _operator);
    }
}
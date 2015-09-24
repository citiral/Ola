//
// Created by citiral on 9/9/15.
//

#include "ExpressionKillerAST.h"
#include "../dast/ExpressionKillerDAST.h"

using namespace llvm;

namespace ola {

    ExpressionKillerAST::ExpressionKillerAST(std::unique_ptr<ExpressionAST> expression)
        : _expression(std::move(expression)) {}

    void ExpressionKillerAST::log(std::ostream &s) {
        _expression->log(s);
        s << ";";
    }

    std::unique_ptr<DASTNode> ExpressionKillerAST::generateDecoratedTree(DastContext& context) {
        return generateDecoratedTreeExpression(context);
    }

    std::unique_ptr<ExpressionDAST> ExpressionKillerAST::generateDecoratedTreeExpression(DastContext& context) {
        return llvm::make_unique<ExpressionKillerDAST>(context, _expression->generateDecoratedTreeExpression(context));
    }
}
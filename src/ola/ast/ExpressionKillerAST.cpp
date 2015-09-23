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

    Value* ExpressionKillerAST::codegen(Context* c) {
        if (_expression)
            _expression->codegen(c);
	    return UndefValue::get(c->builder.getVoidTy());
    }

    std::unique_ptr<ExpressionDAST> ExpressionKillerAST::generateDecoratedTree(DastContext& context) {
        return llvm::make_unique<ExpressionKillerDAST>(context, _expression->generateDecoratedTree(context));
    }
}
//
// Created by Citiral on 16/09/2015.
//

#include "ExpressionKillerDAST.h"

namespace ola {
    
    ExpressionKillerDAST::ExpressionKillerDAST(ola::DastContext& dt, std::unique_ptr<ola::ExpressionDAST> expression)
            : ExpressionDAST(dt),
              _expression(std::move(expression)) {
}

    Type* ExpressionKillerDAST::getType() {
        return _context.typeList.getType("void");
    }

    llvm::Value* ExpressionKillerDAST::codegen(Context* c) {
        if (_expression)
            _expression->codegen(c);
        return llvm::UndefValue::get(c->builder.getVoidTy());
    }

}
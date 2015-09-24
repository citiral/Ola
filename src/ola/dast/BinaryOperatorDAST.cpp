//
// Created by Citiral on 14/09/2015.
//

#include "BinaryOperatorDAST.h"
#include "../dastassert.h"

namespace ola {
    BinaryOperatorDAST::BinaryOperatorDAST(DastContext& dt, std::unique_ptr<ExpressionDAST> lhs, std::unique_ptr<ExpressionDAST> rhs, char opp)
        : ExpressionDAST(dt),
          _lhs(std::move(lhs)),
          _rhs(std::move(rhs)),
          _opp(opp)
    {
        DAST_ASSERT(_lhs->getType()->equals(_rhs->getType()), "Incompatible types in binary operator");
    }

    llvm::Value* BinaryOperatorDAST::codegen(Context* c) {
        //first codegen both arms
        auto LHS = _lhs->codegen(c);
        auto RHS = _rhs->codegen(c);

        if (!LHS || !RHS)
            return nullptr;

        CODEGEN_ASSERT(LHS->getType() == RHS->getType(), "Types in binary operation should be equal.");

        if (_opp == '+')
            return c->builder.CreateAdd(LHS, RHS, "binadd");
        if (_opp == '-')
            return c->builder.CreateSub(LHS, RHS, "binsub");
        if (_opp == '*')
            return c->builder.CreateMul(LHS, RHS, "binmul");
        if (_opp == '/')
            return c->builder.CreateSDiv(LHS, RHS, "bindiv");

        CODEGEN_RETURN_ERROR("Unknown operator '" << _opp << "'");
    }

    Type* BinaryOperatorDAST::getType() {
        return _type;
    }
}

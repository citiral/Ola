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

    Type* BinaryOperatorDAST::getType() {
        return _type;
    }
}

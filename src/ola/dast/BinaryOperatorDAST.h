//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_BINARYOPERATORDAST_H
#define OLA_BINARYOPERATORDAST_H

#include "ExpressionDAST.h"
#include <memory>

namespace ola {
    class BinaryOperatorDAST : public ExpressionDAST {
    public:
        BinaryOperatorDAST(DastContext& dt, std::unique_ptr<ExpressionDAST> lhs, std::unique_ptr<ExpressionDAST> rhs, char opp);
        Type* getType();

    private:
        //the returning type of the operator
        Type* _type;
        //the left and right hand expressions this operates on
        std::unique_ptr<ExpressionDAST> _lhs;
        std::unique_ptr<ExpressionDAST> _rhs;
        //the type of operator that is executed
        char _opp;
    };
}


#endif //OLA_BINARYOPERATORDAST_H

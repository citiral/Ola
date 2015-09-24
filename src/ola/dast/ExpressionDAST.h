//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_EXPRESSIONDAST_H
#define OLA_EXPRESSIONDAST_H

#include "DASTNode.h"
#include "../type/Type.h"
#include <llvm/IR/Value.h>
#include "../codegen/Context.h"

namespace ola {

    class ExpressionDAST : public DASTNode {
    public:
        ExpressionDAST(DastContext& dt) : DASTNode(dt) {}

        //generates llvm IR code using the given context
        virtual llvm::Value* codegen(Context* c) = 0;

        //virtual method which returns the type of this expression
        virtual Type* getType() = 0;
    };

}


#endif //OLA_EXPRESSIONDAST_H

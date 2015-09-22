//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_EXPRESSIONDAST_H
#define OLA_EXPRESSIONDAST_H

#include "DASTNode.h"
#include "../type/Type.h"

namespace ola {

    class ExpressionDAST : public DASTNode {
    public:
        ExpressionDAST(DastContext& dt) : DASTNode(dt) {}
        //virtual method which returns the type of this expression
        virtual Type* getType() = 0;
    };

}


#endif //OLA_EXPRESSIONDAST_H

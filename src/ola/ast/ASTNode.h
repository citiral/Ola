//
// Created by citiral on 9/8/15.
//

#ifndef OLA_ASTNODE_H
#define OLA_ASTNODE_H

#include <ostream>
#include "../passes/TypePass.h"

#define NODE_VISITOR_FUNCTION(R, P) \
virtual R visit(P& pass) {\
    return pass.accept(this);\
}

#define NODE_VISITOR_FUNCTIONS \
NODE_VISITOR_FUNCTION(void, TypePass)

namespace ola {
    class ASTNode {
    public:
        NODE_VISITOR_FUNCTIONS
        virtual ~ASTNode() { };
        virtual void log(std::ostream &s) = 0;
    };
}


#endif //OLA_ASTNODE_H

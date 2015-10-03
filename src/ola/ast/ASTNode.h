//
// Created by citiral on 9/8/15.
//

#ifndef OLA_ASTNODE_H
#define OLA_ASTNODE_H

#include <ostream>
#include "../passes/AbstractPass.h"

#define AST_NODE \
public:\
virtual void visit(AbstractPass& pass) {\
    pass.accept(this);\
}

#define ABSTRACT_AST_NODE \
public:\
virtual void visit(AbstractPass& pass) = 0;

namespace ola {
    class ASTNode {
    ABSTRACT_AST_NODE
    public:
        virtual ~ASTNode() { };
    };
}


#endif //OLA_ASTNODE_H

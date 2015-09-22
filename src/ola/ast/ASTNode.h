//
// Created by citiral on 9/8/15.
//

#ifndef OLA_ASTNODE_H
#define OLA_ASTNODE_H

#include <ostream>
#include "../dast/DASTNode.h"

namespace ola {
    class ASTNode {
    public:
        virtual ~ASTNode() { };

        virtual void log(std::ostream &s) = 0;
    };
}


#endif //OLA_ASTNODE_H

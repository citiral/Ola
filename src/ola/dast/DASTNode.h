//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_DASTNODE_H
#define OLA_DASTNODE_H

#include "DastContext.h"

#define NODE_FUNCTION_CAST(T, x) ((std::unique_ptr<T>(*)(DastContext&))x)

namespace ola {

    class DASTNode {
    public:
        DASTNode(DastContext& dc) : _context(dc) {};
        virtual ~DASTNode() {};

    protected:
        DastContext& _context;
    };

}


#endif //OLA_DASTNODE_H

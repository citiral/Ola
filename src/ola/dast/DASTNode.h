//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_DASTNODE_H
#define OLA_DASTNODE_H

#include "DastContext.h"

namespace ola {

    class DASTNode {
    public:
        DASTNode(DastContext& dc) : _context(dc) {};

    protected:
        DastContext& _context;
    };

}


#endif //OLA_DASTNODE_H

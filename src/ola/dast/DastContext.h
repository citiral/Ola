//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_DASTCONTEXT_H
#define OLA_DASTCONTEXT_H

#include "../type/TypeList.h"
#include "VariableStack.h"
#include <map>
#include <string>

namespace ola {
    class DastContext {
    public:
        DastContext();
        TypeList typeList;
        std::unique_ptr<VariableStack> variableStack;
        void pushVariableStack();
        void popVariableStack();
    };
}

#endif //OLA_DASTCONTEXT_H

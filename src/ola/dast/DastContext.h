//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_DASTCONTEXT_H
#define OLA_DASTCONTEXT_H

#include "../type/TypeList.h"
#include "VariableStack.h"
#include "../ast/FunctionPrototypeAST.h"
#include <map>
#include <string>
#include <stack>

namespace ola {
    class FunctionPrototypeDAST;

    class DastContext {
    public:
        DastContext();
        TypeList typeList;
        std::unique_ptr<VariableStack> variableStack;

        void pushVariableStack();
        void popVariableStack();

        FunctionPrototypeDAST* getFunction(std::string);
        void setFunction(std::string, FunctionPrototypeAST* function);
        void removeFunction(std::string);

    private:
        std::map<std::string, FunctionPrototypeDAST*> _functionMap;
    };
}

#endif //OLA_DASTCONTEXT_H

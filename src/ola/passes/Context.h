//
// Created by Citiral on 30/09/2015.
//

#ifndef OLA_CONTEXT_H
#define OLA_CONTEXT_H

#include "../adt/StackMap.h"
#include "../type/Type.h"


namespace ola {
    class FunctionPrototypeAST;

    class Context {
    public:
        Context();
        StackMap<std::string, Type*> types;
        StackMap<std::string, Type*> variables;
        StackMap<std::string, FunctionPrototypeAST*> functions;
    };
}


#endif //OLA_CONTEXT_H

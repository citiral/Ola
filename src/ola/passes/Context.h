//
// Created by Citiral on 30/09/2015.
//

#ifndef OLA_CONTEXT_H
#define OLA_CONTEXT_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include "../adt/StackMap.h"
#include "../type/Type.h"

namespace ola {
    class FunctionPrototypeAST;

    class Context {
    public:
        Context();
        //AST - Type related maps
        StackMap<std::string, Type*> types;
        StackMap<std::string, Type*> variables;
        StackMap<std::string, FunctionPrototypeAST*> functions;

        //LLVM related items
        StackMap<std::string, llvm::Function*> llvmFunctions;
        StackMap<std::string, llvm::Value*> llvmVariables;
        llvm::IRBuilder<> llvmBuilder;
        llvm::Module llvmModule;

        //composite functions
        void pushAll();
        void popAll();
    };
}


#endif //OLA_CONTEXT_H

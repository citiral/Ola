//
// Created by citiral on 9/9/15.
//

#ifndef OLA_CONTEXT_H
#define OLA_CONTEXT_H

#include <memory>
#include "Scope.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

namespace ola {
    class Context {
    public:
        Context();
        ~Context();

        /*********************************\
        *scope related functions         *
        \*********************************/
        Scope* getScope() const;
        void pushScope();
        void popScope();

        /*********************************\
        *type related functions          *
        \*********************************/
        llvm::Type* getType(std::string name);
        llvm::Type* getPrimitiveType(std::string name);

        std::unique_ptr<llvm::Module> module;
        llvm::IRBuilder<> builder;
    private:
        std::unique_ptr<Scope>_scope;
    };
}


#endif //OLA_CONTEXT_H

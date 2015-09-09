//
// Created by citiral on 9/9/15.
//

#ifndef OLA_SCOPE_H
#define OLA_SCOPE_H

#include <memory>
#include <map>
#include <llvm/IR/Value.h>

namespace ola {
    /**
     * A scope holds his own symbol table and has a reference to its parent scope.
     * Whenever a symbol is requested from a scope, it searches in its own symbol table. If it is not found,
     * it recursively searches in the parent. When no parent is present and the symbol is not found, nullptr is returned
     */
    class Scope {
    public:
        Scope();
        Scope(std::unique_ptr<Scope> parent);

        void addFunction(std::string name, llvm::Function* func);
        llvm::Function* getFunction(std::string name);
        void addVariable(std::string name, llvm::Value* val);
        llvm::Value* getVariable(std::string name);

        std::unique_ptr<Scope> getParent();
    private:
        std::map<std::string, llvm::Function*> _functionTable;
        std::map<std::string, llvm::Value*> _variableTable;
        std::unique_ptr<Scope> _parent;
    };
}


#endif //OLA_SCOPE_H

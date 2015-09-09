//
// Created by citiral on 9/9/15.
//

#include "Scope.h"

namespace ola {

    Scope::Scope():
        _parent(nullptr) {
    }

    Scope::Scope(std::unique_ptr<Scope> parent):
        _parent(std::move(parent)) {
    }

    llvm::Function *Scope::getFunction(std::string name) {
        auto func = _functionTable[name];
        if (func)
            return func;
        else if (_parent)
            return _parent->getFunction(name);
        return nullptr;
    }

    void Scope::addFunction(std::string name, llvm::Function *func) {
        _functionTable[name] = func;
    }

    std::unique_ptr<Scope> Scope::getParent() {
        return std::move(_parent);
    }

    void Scope::addVariable(std::string name, llvm::Value *val) {
        _variableTable[name] = val;
    }

    llvm::Value *Scope::getVariable(std::string name) {
        auto val = _variableTable[name];
        if (val)
            return val;
        else if (_parent)
            return _parent->getVariable(name);
        return nullptr;
    }
}
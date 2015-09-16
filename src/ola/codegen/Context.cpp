//
// Created by citiral on 9/9/15.
//

#include <iostream>
#include "Context.h"

using namespace llvm;

namespace ola {

    Context::Context()
        : module(llvm::make_unique<Module>("Ola", getGlobalContext())),
          builder(getGlobalContext()),
          _scope(new Scope())
    {
    }

    Context::~Context() {
    }

    Scope *Context::getScope() const {
        return _scope.get();
    }

    void Context::pushScope() {
        _scope = llvm::make_unique<Scope>(std::move(_scope));
    }

    void Context::popScope() {
        _scope = _scope->getParent();
    }

    llvm::Type* Context::getType(std::string name) {
        auto type = getPrimitiveType(name);
        if (type)
            return type;
        else {
            //must be a user defined type, check the scope
            std::cout << "TODO: USER DEFINED TYPES.";
            return nullptr;
        }
    }

    llvm::Type* Context::getPrimitiveType(std::string name) {
        if (name.compare("i16") == 0)
            return builder.getInt16Ty();
        if (name.compare("i32") == 0)
            return builder.getInt32Ty();
        if (name.compare("i64") == 0)
            return builder.getInt64Ty();
        if (name.compare("f32") == 0)
            return builder.getFloatTy();
        if (name.compare("f64") == 0)
            return builder.getDoubleTy();
        else
            return nullptr;
    }
}
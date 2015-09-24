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
}
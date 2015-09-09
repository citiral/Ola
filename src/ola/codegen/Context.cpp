//
// Created by citiral on 9/9/15.
//

#include "Context.h"

using namespace llvm;

namespace ola {

    Context::Context()
        : module(std::make_unique<Module>("Ola", getGlobalContext())),
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
        _scope = std::make_unique<Scope>(std::move(_scope));
    }

    void Context::popScope() {
        _scope = _scope->getParent();
    }
}
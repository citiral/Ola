//
// Created by citiral on 9/8/15.
//

#include "VariableAST.h"
#include "../codegenassert.h"

namespace ola {
    VariableAST::VariableAST(std::string name)
            : _name(name) { }

    void VariableAST::log(std::ostream &s) {
        s << "var: " << _name;
    }

    llvm::Value* VariableAST::codegen(Context *c) {
        llvm::Value* value = c->getScope()->getVariable(_name);
        CODEGEN_ASSERT(value != nullptr, "Undefined variable " << _name);
        return value;
    }
}
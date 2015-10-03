//
// Created by citiral on 9/8/15.
//

#include "VariableAST.h"
#include "../codegenassert.h"

namespace ola {
    VariableAST::VariableAST(std::string name)
            : _name(name),
        _type(nullptr) { }

    Type* VariableAST::getType() {
        return _type;
    }

    void VariableAST::setType(Type* type) {
        _type = type;
    }

    std::string VariableAST::getName() {
        return _name;
    }
}
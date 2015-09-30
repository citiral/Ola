//
// Created by citiral on 9/8/15.
//

#include <llvm/ADT/STLExtras.h>
#include "NumberIntegerAST.h"

using namespace llvm;

namespace ola {
    NumberIntegerAST::NumberIntegerAST(i32 value)
            : _value(value) { }

    void NumberIntegerAST::log(std::ostream &s) {
        s << "i32: " << _value;
    }

    std::unique_ptr<NumberIntegerAST> NumberIntegerAST::generate(Lexer &l) {
        i64 number = atol(l.value.string.c_str());
        l.nextToken();
        return llvm::make_unique<NumberIntegerAST>(number);
    }

    Type* NumberIntegerAST::getType() {
        return _type;
    }

    void NumberIntegerAST::setType(Type* type) {
        _type = type;
    }
}
//
// Created by citiral on 9/8/15.
//

#include <llvm/ADT/STLExtras.h>
#include "NumberIntegerAST.h"

using namespace llvm;

namespace ola {
    NumberIntegerAST::NumberIntegerAST(Lexer& l, i32 value):
            ExpressionAST(l),
            _value(value),
            _type(nullptr) { }

    std::unique_ptr<NumberIntegerAST> NumberIntegerAST::generate(Lexer &l) {
        i64 number = atol(l.value.string.c_str());
        l.nextToken();
        return llvm::make_unique<NumberIntegerAST>(l, number);
    }

    Type* NumberIntegerAST::getType() {
        return _type;
    }

    void NumberIntegerAST::setType(Type* type) {
        _type = type;
    }

    i32 NumberIntegerAST::getValue() {
        return _value;
    }
}
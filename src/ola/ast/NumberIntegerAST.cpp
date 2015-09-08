//
// Created by citiral on 9/8/15.
//

#include "NumberIntegerAST.h"

namespace ola {
    NumberIntegerAST::NumberIntegerAST(i64 value)
            : _value(value) { }

    void NumberIntegerAST::log(std::ostream &s) {
        s << "i32: " << _value;
    }

    std::string NumberIntegerAST::type() {
        return "i64";
    }

    std::unique_ptr<NumberIntegerAST> NumberIntegerAST::generate(Lexer &l) {
        i64 number = atol(l.value.string.c_str());
        l.nextToken();
        return std::make_unique<NumberIntegerAST>(number);
    }
}
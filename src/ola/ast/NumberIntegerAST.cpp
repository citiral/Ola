//
// Created by citiral on 9/8/15.
//

#include "NumberIntegerAST.h"
#include "../dast/NumberIntegerDAST.h"
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

    std::unique_ptr<DASTNode> NumberIntegerAST::generateDecoratedTree(DastContext& context) {
        return generateDecoratedTreeExpression(context);
    }

    std::unique_ptr<ExpressionDAST> NumberIntegerAST::generateDecoratedTreeExpression(DastContext& context) {
        return llvm::make_unique<NumberIntegerDAST>(context, _value);
    }
}
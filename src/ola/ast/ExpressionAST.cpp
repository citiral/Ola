//
// Created by citiral on 9/8/15.
//

#include "ExpressionAST.h"
#include "NumberIntegerAST.h"
#include "../compileassert.h"

namespace ola {
    ExpressionAST::~ExpressionAST() {
    }

    std::unique_ptr<ExpressionAST> ExpressionAST::generate(Lexer &l) {
        switch (l.curToken()) {
            case Token::Numeric:
                return NumberIntegerAST::generate(l);
            default:
                COMPILE_GENERATE_AND_RETURN_ERROR(l, "Unknown token in expression");
        }
    }
}
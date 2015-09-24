//
// Created by Citiral on 24/09/2015.
//

#include "TypePass.h"
#include <iostream>

namespace ola {

    void TypePass::accept(ASTNode* a) {
        std::cout << "TypePass not implemented for ASTNODE";
    }

    void TypePass::accept(BinaryOperatorAST* ast) {

    }

    void TypePass::accept(ExpressionAST* ast) {

    }

    void TypePass::accept(ExpressionKillerAST* ast) {

    }

    void TypePass::accept(ExpressionSeriesAST* ast) {

    }

    void TypePass::accept(FunctionAST* ast) {

    }

    void TypePass::accept(FunctionCallAST* ast) {

    }

    void TypePass::accept(FunctionPrototypeAST* ast) {

    }

    void TypePass::accept(NumberIntegerAST* ast) {

    }

    void TypePass::accept(VariableAST* ast) {

    }
}

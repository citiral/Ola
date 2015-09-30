//
// Created by Citiral on 24/09/2015.
//

#include "TypePass.h"
#include <iostream>
#include "../ast/BinaryOperatorAST.h"
#include "../ast/ExpressionKillerAST.h"
#include "../ast/ExpressionSeriesAST.h"
#include "../ast/FunctionAST.h"
#include "../ast/FunctionCallAST.h"
#include "../ast/FunctionPrototypeAST.h"
#include "../ast/NumberIntegerAST.h"
#include "../ast/VariableAST.h"

namespace ola {

    TypePass::TypePass(DastContext& dc):
        _dc(dc) {

    }

    void TypePass::accept(ASTNode* a) {
        std::cout << "TypePass not implemented for ASTNODE";
    }

    void TypePass::accept(BinaryOperatorAST* ast) {
        ast->getLeftExpression()->visit(*this);
        ast->getRightExpression()->visit(*this);
        if (ast->getLeftExpression()->getType()->equals(ast->getRightExpression()->getType())) {
            ast->setType(ast->getLeftExpression()->getType());
        }
    }

    void TypePass::accept(ExpressionAST* ast) {

    }

    void TypePass::accept(ExpressionKillerAST* ast) {
        ast->setType(_dc.typeList.getType("void"));
    }

    void TypePass::accept(ExpressionSeriesAST* ast) {
        for (u32 i = 0 ; i < ast->getBody()->size() ; i++)
            ast->getBody()->at(i)->visit(*this);
        ast->setType((*ast->getBody()->end())->getType());

    }

    void TypePass::accept(FunctionAST* ast) {
        //generate the prototype
        ast->getPrototype()->visit(*this);
        //register the arguments on the variable stack

        //then compile the series
        ast->getExpressionSeries()->visit(*this);
    }

    void TypePass::accept(FunctionCallAST* ast) {
        ast->setType(_dc.getFunction(ast->getFunctionName())->getType());
    }

    void TypePass::accept(FunctionPrototypeAST* ast) {
        //first, initialize the prototype types
        ast->setType(_dc.typeList.getType(ast->getTypeName()));
        //then register it in the context
        _dc.setFunction(ast->getFunctionName(), ast);
    }

    void TypePass::accept(NumberIntegerAST* ast) {
        ast->setType(_dc.typeList.getType("u32"));
    }

    void TypePass::accept(VariableAST* ast) {
        ast->setType(_dc.variableStack->getVariable(ast->getName()));
    }
}

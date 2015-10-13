//
// Created by Citiral on 24/09/2015.
//

#include "TypePass.h"
#include <iostream>
#include "../types.h"
#include "../ast/BinaryOperatorAST.h"
#include "../ast/ExpressionKillerAST.h"
#include "../ast/ExpressionSeriesAST.h"
#include "../ast/FunctionPrototypeAST.h"
#include "../ast/FunctionAST.h"
#include "../ast/FunctionCallAST.h"
#include "../ast/NumberIntegerAST.h"
#include "../ast/VariableAST.h"

namespace ola {

    TypePass::TypePass(Context& c):
        _c(c) {

    }

    void TypePass::accept(ASTNode* a) {
        std::cout << "TypePass not implemented for ASTNode";
    }

    void TypePass::accept(BinaryOperatorAST* ast) {
        ast->getLeftExpression()->visit(*this);
        ast->getRightExpression()->visit(*this);

        //todo create invalid type
        if (ast->getLeftExpression()->getType() == nullptr || ast->getRightExpression()->getType() == nullptr) {
            PASS_ERROR("NULL type in binary operator");
            ast->setType(nullptr);
            return;
        }

        //todo coerce types
        PASS_ASSERT(ast->getLeftExpression()->getType()->equals(ast->getRightExpression()->getType()), "Incompatible types in binary operator.");

        //todo get the implicit type here if something has to be cast
        ast->setType(_c.types.getValue("i32"));
    }

    void TypePass::accept(ExpressionAST* ast) {
        std::cout << "TypePass not implemented for ExpressionAST";
    }

    void TypePass::accept(ExpressionKillerAST* ast) {
        ast->setType(_c.types.getValue("void"));
    }

    void TypePass::accept(ExpressionSeriesAST* ast) {
        for (u32 i = 0 ; i < ast->getBody()->size() ; i++)
            ast->getBody()->at(i)->visit(*this);
        ast->setType(ast->getBody()->back()->getType());

    }

    void TypePass::accept(FunctionAST* ast) {
        //generate the prototype
        ast->getPrototype()->visit(*this);

        //register the arguments on the variable stack
        _c.variables.pushMap();
        u32 argsCount = ast->getPrototype()->getArgsNames().size();
        for (u32 i = 0 ; i < argsCount ; i++) {
            _c.variables.addValue(ast->getPrototype()->getArgsNames()[i], ast->getPrototype()->getArgsTypes()[i]);
        }

        //then compile the series
        ast->getExpressionSeries()->visit(*this);
        //and pop the variables from the stack
        _c.variables.popMap();
    }

    void TypePass::accept(FunctionCallAST* ast) {
        //first, set the type of all arguments
        for (u32 i = 0 ; i < ast->getArgs()->size() ; i++)
            ast->getArgs()->at(i)->visit(*this);

        //TODO: name wrangling here

        //then, set the return type of the function call
        ast->setType((_c.functions.getValue(ast->getFunctionName()))->getType());
    }

    void TypePass::accept(FunctionPrototypeAST* ast) {
        //first, initialize the prototype types
        ast->setType(_c.types.getValue(ast->getTypeName()));

        //setup the types
        std::vector<Type*> types;
        u64 argsCount = ast->getArgsTypesNames().size();
        for (u64 i = 0 ; i < argsCount ; i++)
            types.push_back(_c.types.getValue(ast->getArgsTypesNames()[i]));
        ast->setArgsTypes(types);

        //then register it in the context
        _c.functions.addValue(ast->getFunctionName(), ast);
    }

    void TypePass::accept(NumberIntegerAST* ast) {
        ast->setType(_c.types.getValue("i32"));
    }

    void TypePass::accept(VariableAST* ast) {
        ast->setType(_c.variables.getValue(ast->getName()));
    }
}

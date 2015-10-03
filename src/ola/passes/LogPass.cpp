//
// Created by Citiral on 3/10/2015.
//

#include "LogPass.h"
#include "../ast/BinaryOperatorAST.h"
#include "../ast/ExpressionKillerAST.h"
#include "../ast/ExpressionSeriesAST.h"
#include "../ast/FunctionPrototypeAST.h"
#include "../ast/FunctionAST.h"
#include "../ast/FunctionCallAST.h"
#include "../ast/NumberIntegerAST.h"
#include "../ast/VariableAST.h"

ola::LogPass::LogPass(std::ostream& s):
    _s(s) {
}

void ola::LogPass::accept(ola::ASTNode* ast) {
    _s << "Unimplemented ASTNode.";
}

void ola::LogPass::accept(ola::BinaryOperatorAST* ast) {
    _s << "(";
    ast->getLeftExpression()->visit(*this);
    _s << ")";
    _s << " " << ast->getOperator() << " ";
    _s << "(";
    ast->getRightExpression()->visit(*this);
    _s << ")";
}

void ola::LogPass::accept(ola::ExpressionAST* ast) {
    _s << "Unimplemented Expression Node.";
}

void ola::LogPass::accept(ola::ExpressionKillerAST* ast) {
    ast->getExpression()->visit(*this);
    _s << ";";
}

void ola::LogPass::accept(ola::ExpressionSeriesAST* ast) {
    _s << "Expression series: ";
    for (u32 i = 0; i < ast->getBody()->size(); i++) {
        ast->getBody()->at(i)->visit(*this);
        _s << "\n";
    }
}

void ola::LogPass::accept(ola::FunctionAST* ast) {
    ast->getPrototype()->visit(*this);
    ast->getExpressionSeries()->visit(*this);
}

void ola::LogPass::accept(ola::FunctionCallAST* ast) {
    _s << ast->getFunctionName() << "(";

    if (ast->getArgs()->size() > 0)
        ast->getArgs()->at(0)->visit(*this);

    for (u32 i = 1 ; i < ast->getArgs()->size() ; i++) {
        _s << ", ";
        ast->getArgs()->at(i)->visit(*this);
    }
    _s << ")";
}

void ola::LogPass::accept(ola::FunctionPrototypeAST* ast) {
    _s << "Function prototype: " << ast->getFunctionName() << "(";

    if (ast->getArgsNames().size() > 0)
        _s << ast->getArgsTypesNames()[0] << " " << ast->getArgsNames()[0];

    for (u32 i = 1; i < ast->getArgsNames().size(); i++) {
        _s << ", " << ast->getArgsTypesNames()[i] << " " << ast->getArgsNames()[i];
    }
    _s << ") -> " << ast->getTypeName() << "\n";
}

void ola::LogPass::accept(ola::NumberIntegerAST* ast) {
    _s << "i32: " << ast->getValue();
}

void ola::LogPass::accept(ola::VariableAST* ast) {
    _s << "var: " << ast->getName();
}

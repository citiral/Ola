//
// Created by Citiral on 6/09/2015.
//

#include "ast.h"

/********************************************
 * ExpressionAST                            *
 ********************************************/
ExpressionAST::~ExpressionAST() { }


/********************************************
 * NumberIntegerAST                         *
 ********************************************/
NumberIntegerAST::NumberIntegerAST(i64 value)
        : _value(value) { }

/********************************************
 * NumberFloatingAST                        *
 ********************************************/
NumberFloatingAST::NumberFloatingAST(f64 value)
        : _value(value) { }

/********************************************
 * VariableAST                              *
 ********************************************/
VariableAST::VariableAST(std::string name)
        : _name(name) { }

/********************************************
 * BinaryOperatorAST                        *
 ********************************************/
BinaryOperatorAST::BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression, std::unique_ptr<ExpressionAST>  rightExpression)
        : _operator(_operator),
          _leftExpression(std::move(leftExpression)),
          _rightExpression(std::move(rightExpression)) { }

/********************************************
 * FunctionPrototypeAST                     *
 ********************************************/
FunctionPrototypeAST::FunctionPrototypeAST(std::string name, std::vector<std::string> args)
        : _name(name),
          _args(std::move(args)){ }

/********************************************
 * FunctionAST                     *
 ********************************************/
FunctionAST::FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionAST> body)
    : _prototype(std::move(prototype)),
    _body(std::move(body)) { }
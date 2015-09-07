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
VariableAST::VariableAST(std::string name, std::string type)
        : _name(name),
          _type(type) { }

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
FunctionPrototypeAST::FunctionPrototypeAST(std::string name, std::vector<std::string> args, std::vector<std::string> types)
        : _name(name),
          _args(std::move(args)),
          _types(types) { }

/********************************************
 * FunctionAST                     *
 ********************************************/
FunctionAST::FunctionAST(std::string type, std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionAST> body)
    : _type(type),
    _prototype(std::move(prototype)),
    _body(std::move(body)) { }
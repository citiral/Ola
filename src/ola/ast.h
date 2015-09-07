//
// Created by Citiral on 6/09/2015.
//

#ifndef OLA_AST_H
#define OLA_AST_H

#include "types.h"
#include <string>
#include <memory>
#include <vector>

/********************************************
 * ExpressionAST                            *
 ********************************************/
class ExpressionAST {
public:
    virtual ~ExpressionAST();
};

/********************************************
 * NumberIntegerAST                         *
 ********************************************/
class NumberIntegerAST : ExpressionAST {
public:
    NumberIntegerAST(i64 value);

private:
    i64 _value;
};

/********************************************
 * NumberFloatingAST                        *
 ********************************************/
class NumberFloatingAST : ExpressionAST {
public:
    NumberFloatingAST(f64 value);

private:
    f64 _value;
};

/********************************************
 * VariableAST                              *
 ********************************************/
class VariableAST : ExpressionAST {
public:
    VariableAST(std::string name, std::string type);

private:
    std::string _name;
    std::string _type;
};

/********************************************
 * BinaryOperatorAST                        *
 ********************************************/
class BinaryOperatorAST : ExpressionAST {
public:
    BinaryOperatorAST(char opp, std::unique_ptr<ExpressionAST> leftExpression, std::unique_ptr<ExpressionAST>  rightExpression);

private:
    char _operator;
    std::unique_ptr<ExpressionAST> _leftExpression;
    std::unique_ptr<ExpressionAST> _rightExpression;
};

/********************************************
 * FunctionPrototypeAST                     *
 ********************************************/
class FunctionPrototypeAST {
public:
    FunctionPrototypeAST(std::string name, std::vector<std::string> args, std::vector<std::string> types);

private:
    std::string _name;
    std::vector<std::string> _args;
    std::vector<std::string> _types;
};

/********************************************
 * FunctionAST                              *
 ********************************************/
class FunctionAST {
public:
    FunctionAST(std::string type, std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionAST> body);

private:
    std::string _type;
    std::unique_ptr<FunctionPrototypeAST> _prototype;
    std::unique_ptr<ExpressionAST> _body;
};



#endif //OLA_AST_H

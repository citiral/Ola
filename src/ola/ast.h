//
// Created by Citiral on 6/09/2015.
//

#ifndef OLA_AST_H
#define OLA_AST_H

#include "types.h"
#include <string>
#include <memory>
#include <vector>
#include <ostream>

class ASTNode {
public:
    virtual ~ASTNode() {};
    virtual void log(std::ostream& s);
};

/********************************************
 * ExpressionAST                            *
 ********************************************/
class StatementAST : public ASTNode {
public:
    virtual ~StatementAST() {};
};

/********************************************
 * ExpressionAST                            *
 ********************************************/
class ExpressionAST : public StatementAST {
public:
    virtual ~ExpressionAST() {};
    virtual std::string type() = 0;
};

/********************************************
 * ExpressionSeriesAST                      *
 ********************************************/
class ExpressionSeriesAST : public ASTNode {
public:
    ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body);
    virtual std::string type();
    virtual void log(std::ostream& s) override;
private:
    std::vector<std::unique_ptr<ExpressionAST>> _body;
};

/********************************************
 * NumberIntegerAST                         *
 ********************************************/
class NumberIntegerAST : public ExpressionAST {
public:
    NumberIntegerAST(i64 value);
    void log(std::ostream& s);
    std::string type() { return "i64"; }
private:
    i64 _value;
};

/********************************************
 * NumberFloatingAST                        *
 ********************************************/
class NumberFloatingAST : public ExpressionAST {
public:
    NumberFloatingAST(f64 value);
    std::string type() { return "f64"; }

private:
    f64 _value;
};

/********************************************
 * VariableAST                              *
 ********************************************/
class VariableAST : public ExpressionAST {
public:
    VariableAST(std::string name, std::string type);
    std::string type() { return _type; }

private:
    std::string _name;
    std::string _type;
};

/********************************************
 * BinaryOperatorAST                        *
 ********************************************/
class BinaryOperatorAST : public ExpressionAST {
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
class FunctionPrototypeAST : public ASTNode {
public:
    FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args, std::vector<std::string> types);
    virtual void log(std::ostream& s);
    std::string type() { return _type; }
private:
    std::string _type;
    std::string _name;
    std::vector<std::string> _args;
    std::vector<std::string> _types;
};

/********************************************
 * FunctionAST                              *
 ********************************************/
class FunctionAST : public ASTNode {
public:
    FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body);
    virtual void log(std::ostream& s);

private:
    std::unique_ptr<FunctionPrototypeAST> _prototype;
    std::unique_ptr<ExpressionSeriesAST> _body;
};

/********************************************
 * ErrorAST                                 *
 ********************************************/
class ErrorAST : public ASTNode {
public:
    ErrorAST(std::string message);
    void log(std::ostream& s);
private:
    std::string _message;
};



#endif //OLA_AST_H

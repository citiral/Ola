//
// Created by Citiral on 6/09/2015.
//

#include "ast.h"

void ASTNode::log(std::ostream &s) {
    s << "Unimplemented log function.\n";
}

/********************************************
 * ExpressionSeriesAST                      *
 ********************************************/
ExpressionSeriesAST::ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body)
    : _body (std::move(body)) {}

std::string ExpressionSeriesAST::type() {
    return _body.back()->type();
}

void ExpressionSeriesAST::log(std::ostream &s) {
    s << "statement series: ";
    for (u32 i = 0 ; i < _body.size() ; i++) {
        _body[i]->log(s);
        s << "\n";
    }
}

/********************************************
 * NumberIntegerAST                         *
 ********************************************/
NumberIntegerAST::NumberIntegerAST(i64 value)
        : _value(value) { }

void NumberIntegerAST::log(std::ostream& s) {
    s << "i32: " << _value;
}

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
        : _operator(opp),
          _leftExpression(std::move(leftExpression)),
          _rightExpression(std::move(rightExpression)) { }

/********************************************
 * FunctionPrototypeAST                     *
 ********************************************/
FunctionPrototypeAST::FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args, std::vector<std::string> types)
        : _type(type),
          _name(name),
          _args(std::move(args)),
          _types(types) { }

void FunctionPrototypeAST::log(std::ostream& s) {
    s << "Function prototype: " << _name << "(";
    if (_args.size() > 0)
        s << _types[0] << " " << _args[0];
    for (u32 i = 1 ; i < _args.size() ; i++) {
        s << ", " << _types[i] << " " << _args[i];
    }
    s << ") -> " << _type << "\n";
}

/********************************************
 * FunctionAST                     *
 ********************************************/
FunctionAST::FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body)
    : _prototype(std::move(prototype)),
    _body(std::move(body)) { }

void FunctionAST::log(std::ostream &s) {
    _prototype->log(s);
    _body->log(s);
}

/********************************************
 * ErrorAST                                 *
 ********************************************/
ErrorAST::ErrorAST(std::string message)
    : _message(message) {}

void ErrorAST::log(std::ostream& s) {
    s << "Error: " << _message << "\n";
}

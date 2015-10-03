//
// Created by Citiral on 3/10/2015.
//

#ifndef OLA_ABSTRACTSTACKPASS_H
#define OLA_ABSTRACTSTACKPASS_H

#include "AbstractPass.h"
#include "../ast/ASTNode.h"
#include <stack>

#define PUSH_AND_RETURN(val)\
{\
    push(val);\
    return;\
}

namespace ola {

    template<class T>
    class AbstractStackPass : public AbstractPass {
        virtual void accept(ASTNode* ast) = 0;
        virtual void accept(BinaryOperatorAST* ast) = 0;
        virtual void accept(ExpressionAST* ast) = 0;
        virtual void accept(ExpressionKillerAST* ast) = 0;
        virtual void accept(ExpressionSeriesAST* ast) = 0;
        virtual void accept(FunctionAST* ast) = 0;
        virtual void accept(FunctionCallAST* ast) = 0;
        virtual void accept(FunctionPrototypeAST* ast) = 0;
        virtual void accept(NumberIntegerAST* ast) = 0;
        virtual void accept(VariableAST* ast) = 0;

    protected:
        //composite stack functions
        T visitAndPop(ASTNode* ast);
        //base stack functions
        T& peek();
        T pop();
        void push(T value);

    private:
        std::stack<T> _stack;
    };

    template<class T>
    T AbstractStackPass<T>::visitAndPop(ASTNode* ast) {
        ast->visit(*this);
        return pop();
    }

    template<class T>
    T& AbstractStackPass<T>::peek() {
        return _stack.top();
    }

    template<class T>
    T AbstractStackPass<T>::pop() {
        T val = _stack.top();
        _stack.pop();
        return std::move(val);
    }

    template<class T>
    void AbstractStackPass<T>::push(T value) {
        _stack.push(value);
    }

}


#endif //OLA_ABSTRACTSTACKPASS_H

//
// Created by Citiral on 3/10/2015.
//

#ifndef OLA_ABSTRACTPASS_H
#define OLA_ABSTRACTPASS_H

#define PASS_ASSERT(X, Y) \
{\
if (!(X)) {\
    std::cout << Y;\
    return;\
}\
}

#define PASS_TODO(Y) \
{\
    std::cout << "TODO at " << __FILE__ << "[" << __LINE__ << "]: " << Y << "\n";\
}

#define PASS_ERROR(Y) \
{\
    std::cout << "ERROR at " << __FILE__ << "[" << __LINE__ << "]: " << Y << "\n";\
}


namespace ola {

    class ASTNode;
    class BinaryOperatorAST;
    class ExpressionAST;
    class ExpressionKillerAST;
    class ExpressionSeriesAST;
    class FunctionAST;
    class FunctionCallAST;
    class FunctionPrototypeAST;
    class NumberIntegerAST;
    class VariableAST;

    class AbstractPass {
    public:
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
    };
}


#endif //OLA_ABSTRACTPASS_H

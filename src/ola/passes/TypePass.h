//
// Created by Citiral on 24/09/2015.
//

#ifndef OLA_TYPEPASS_H
#define OLA_TYPEPASS_H

#include "../dast/DastContext.h"

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

    class TypePass {
    public:
        TypePass(DastContext& dc);

        void accept(ASTNode* ast);
        void accept(BinaryOperatorAST* ast);
        void accept(ExpressionAST* ast);
        void accept(ExpressionKillerAST* ast);
        void accept(ExpressionSeriesAST* ast);
        void accept(FunctionAST* ast);
        void accept(FunctionCallAST* ast);
        void accept(FunctionPrototypeAST* ast);
        void accept(NumberIntegerAST* ast);
        void accept(VariableAST* ast);

    private:
        DastContext& _dc;
    };
}


#endif //OLA_TYPEPASS_H

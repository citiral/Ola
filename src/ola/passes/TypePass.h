//
// Created by Citiral on 24/09/2015.
//

#ifndef OLA_TYPEPASS_H
#define OLA_TYPEPASS_H

#include "Context.h"
#include "AbstractPass.h"

namespace ola {

    class TypePass : public AbstractPass {
    public:
        TypePass(Context& dc);

        void accept(ASTNode* ast) override;
        void accept(BinaryOperatorAST* ast) override;
        void accept(ExpressionAST* ast) override;
        void accept(ExpressionKillerAST* ast) override;
        void accept(ExpressionSeriesAST* ast) override;
        void accept(FunctionAST* ast) override;
        void accept(FunctionCallAST* ast) override;
        void accept(FunctionPrototypeAST* ast) override;
        void accept(NumberIntegerAST* ast) override;
        void accept(VariableAST* ast) override;

    private:
        Context& _c;
    };
}


#endif //OLA_TYPEPASS_H

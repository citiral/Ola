//
// Created by Citiral on 3/10/2015.
//

#ifndef OLA_CODEGENPASS_H
#define OLA_CODEGENPASS_H

#include <llvm/IR/Value.h>
#include "AbstractStackPass.h"
#include "Context.h"

namespace ola {

    class CodegenPass : public AbstractStackPass<llvm::Value*> {
    public:
        CodegenPass(Context& c);

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
        //llvm::Function* _lastFunction;
        Context& _c;
    };
}

#endif //OLA_CODEGENPASS_H

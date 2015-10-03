//
// Created by Citiral on 3/10/2015.
//

#ifndef OLA_LOGPASS_H
#define OLA_LOGPASS_H

#include <ostream>
#include "AbstractPass.h"

namespace ola {

    class LogPass : public AbstractPass {
    public:
        LogPass(std::ostream& s);

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
        std::ostream &_s;
    };
}

#endif //OLA_LOGPASS_H

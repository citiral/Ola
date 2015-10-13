//
// Created by citiral on 9/9/15.
//

#ifndef OLA_EXPRESSIONKILLERAST_H
#define OLA_EXPRESSIONKILLERAST_H

#include "ASTNode.h"
#include "ExpressionAST.h"
#include <memory>

namespace ola {
    class ExpressionKillerAST : public ExpressionAST {
    AST_NODE
    public:
        ExpressionKillerAST(Lexer& l, std::unique_ptr<ExpressionAST> expression);

        Type* getType() override;
        void setType(Type* type);
        ExpressionAST* getExpression();
    private:
        Type* _type;
        std::unique_ptr<ExpressionAST> _expression;
    };
}


#endif //OLA_EXPRESSIONKILLERAST_H

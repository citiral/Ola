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
    public:
        NODE_VISITOR_FUNCTIONS
        ExpressionKillerAST(std::unique_ptr<ExpressionAST> expression);

        virtual void log(std::ostream &s) override;

        std::unique_ptr<DASTNode> generateDecoratedTree(DastContext& context) override;
        std::unique_ptr<ExpressionDAST> generateDecoratedTreeExpression(DastContext& context) override;

        Type* getType() override;
    private:
        Type* _type;
        std::unique_ptr<ExpressionAST> _expression;
    };
}


#endif //OLA_EXPRESSIONKILLERAST_H

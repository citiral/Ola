//
// Created by citiral on 9/8/15.
//

#ifndef OLA_EXPRESSIONAST_H
#define OLA_EXPRESSIONAST_H

#include "ASTNode.h"
#include "../lexer.h"
#include <memory>
#include <llvm/IR/Value.h>
#include "../codegen/Context.h"
#include "../dast/ExpressionDAST.h"
#include "../dast/DastContext.h"

namespace ola {
    class ExpressionAST : public ASTNode {
    public:
        virtual ~ExpressionAST();

        //generates llvm IR code using the given context
        virtual llvm::Value* codegen(Context* c) = 0;

        static std::unique_ptr<ExpressionAST> generate(Lexer& l);
        static std::unique_ptr<ExpressionAST> generatePrimary(Lexer& l);
        static std::unique_ptr<ExpressionAST> generateIdentifier(Lexer& l);

        virtual std::unique_ptr<ExpressionDAST> generateDecoratedTree(DastContext& context) = 0;
    };
}

#endif //OLA_EXPRESSIONAST_H

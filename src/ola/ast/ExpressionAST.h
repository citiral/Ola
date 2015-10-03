//
// Created by citiral on 9/8/15.
//

#ifndef OLA_EXPRESSIONAST_H
#define OLA_EXPRESSIONAST_H

#include "ASTNode.h"
#include "../lexer.h"
#include <memory>
#include <llvm/IR/Value.h>
#include "../type/Type.h"

namespace ola {
    class ExpressionAST : public ASTNode {
    ABSTRACT_AST_NODE
    public:
        virtual ~ExpressionAST();

        virtual Type* getType() = 0;

        static std::unique_ptr<ExpressionAST> generate(Lexer& l);
        static std::unique_ptr<ExpressionAST> generatePrimary(Lexer& l);
        static std::unique_ptr<ExpressionAST> generateIdentifier(Lexer& l);
    };
}

#endif //OLA_EXPRESSIONAST_H

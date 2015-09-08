//
// Created by citiral on 9/8/15.
//

#ifndef OLA_EXPRESSIONAST_H
#define OLA_EXPRESSIONAST_H

#include "ASTNode.h"
#include "../lexer.h"
#include <memory>

namespace ola {
    class ExpressionAST : public ASTNode {
    public:
        virtual ~ExpressionAST();

        virtual std::string type() = 0;

        static std::unique_ptr<ExpressionAST> generate(Lexer& l);
        static std::unique_ptr<ExpressionAST> generatePrimary(Lexer& l);
    };
}

#endif //OLA_EXPRESSIONAST_H

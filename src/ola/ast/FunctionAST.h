//
// Created by citiral on 9/8/15.
//

#ifndef OLA_FUNCTIONAST_H
#define OLA_FUNCTIONAST_H

#include "ASTNode.h"
#include "FunctionPrototypeAST.h"
#include "ExpressionSeriesAST.h"
#include <memory>

namespace ola {
    class FunctionAST : public ASTNode {
    AST_NODE
    public:
        FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body);

        static std::unique_ptr<FunctionAST> generate(Lexer& l);

        FunctionPrototypeAST* getPrototype();
        ExpressionSeriesAST* getExpressionSeries();

    private:
        std::unique_ptr<FunctionPrototypeAST> _prototype;
        std::unique_ptr<ExpressionSeriesAST> _body;
    };
}

#endif //OLA_FUNCTIONAST_H
